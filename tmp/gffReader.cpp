//
//  gffReader.cpp
//  fast_science
//
//
//  Created by Manuel on 20.06.15.
//
//

#include "gffReader.h"

void fs::GffReader::GffInit() {
  
  // Version 0 means an invalid number!
  this->_version = 0;
  
  // all .gff files have the same delimiters
  this->_defaultDelimiter = '\t';
  this->_attributeDelimiter = ';';
  
  // maybe we know already the version from the suffix?
  if (this->_suffix->compare("gtf") == 0) {
    this->_version = 2;
    this->_keyValueDelimiter = ' ';
  }
}


fs::GffReader::GffReader(std::string const file, std::string const path) : fs::Reader<fs::GffFormat>(file, path) {
  
  GffInit();
}

fs::GffReader::GffReader(std::string const & fileWithPath) : fs::Reader<fs::GffFormat>(fileWithPath) {
  
  GffInit();
}

fs::GffReader::~GffReader() {
  
}

void fs::GffReader::readFromFile(std::list<fs::GffFormat> & data) {
  
  // open the file
  std::fstream datafile;

  try {

    datafile.open(*(this->_path) + *(this->_file) + *(this->_suffix), std::fstream::in | std::fstream::binary);
    
    if (datafile.is_open()){
      std::string line;
      // go through each line
      unsigned int line_counter = 0;
      
      while (getline (datafile,line)) {
        ++line_counter;
        
        
        // first, chomp all lines which are maked as comments
        
        std::string first_two = line.substr(0,2);
        
        bool comment = false;
        
        for ( auto it = this->_comment->cbegin(); it != this->_comment->end(); ++it ) {
          if (string_contains_string(first_two, *it)) {
            comment = true;
          }
        }
        
        if (comment == true) {
          continue;
        }
        
        // second, remove any endline or separator character at the end of the line
        if (line.back() == '\n')
          line.pop_back();
        
        while (line.back() == this->_defaultDelimiter || line.back() == this->_attributeDelimiter || line.back() == this->_keyValueDelimiter) {
          line.pop_back();
        }
        
        // third, check for each liner if ther are at least 7 values
        unsigned int counter = std::count (line.begin(), line.end(), this->_defaultDelimiter);
        if (counter < 7) {
          // This should not happen!
          throw fs::Exception("Unvalide string: \"" + line + "\" at line: " + std::to_string(line_counter));
        }
        

        
        // if the version is not clear, try to figure it out from the first non-comment line.
        // if there are only 7 values in one line we don't have to care, but if there are 8 the things become more tricky. Version 1 has only a single attribute string, but vesion 2 and 3 have attributes separated by ';'
        
        // go thorogh all this only if the version in unknown yet.
        if (this->_version == 0) {
          
          unsigned int counter = std::count (line.begin(), line.end(), this->_defaultDelimiter);
          
          
          if (counter < 7) {
            // This should not happen!
            throw fs::Exception("Unvalide string: \"" + line + "\" at line: " + std::to_string(line_counter));
            
          } else if (counter == 7) {
            // in that case the version does not matter. Let's take version 1 for simplicity
            this->_version = 1;
            
          } else {
            
            // now we must see if the attribute string can be split into key - value fragments with the attribute delimiter
            // key values are separated by either ' ' for version 2 or by '=' for version 3.
            
            std::size_t found = std::string::npos;
            found = line.find_last_of(this->_defaultDelimiter);
            
            std::string tmp_str;
            tmp_str=line.substr(found+1);
            
            // let's see if there is a key value separater as often as there are attributes

            unsigned int counter1 = std::count (line.begin(), line.end(), this->_attributeDelimiter);
            unsigned int conuter2 = std::count (line.begin(), line.end(), ' ');
            unsigned int counter3 = std::count (line.begin(), line.end(), '=');
            
            if (counter1 > 0 && counter1 < counter3) {
              this->_version = 3;
              this->_keyValueDelimiter = '=';
            } else if (counter1 < conuter2) {
              this->_version = 2;
              this->_keyValueDelimiter = ' ';
            } else {
              this->_version = 1;
            }
          }
        }
      

        // Now add the lines to the data list
        fs::GffFormat tmp_gff;
        std::size_t found = std::string::npos;
        
        // Split the line at every delimiter and store the elements in the GFF object;
        
        // the seqname
        found = line.find(this->_defaultDelimiter);
        tmp_gff.setSeqname(line.substr(0, found));
        line = line.substr(found+1);
        
        // the source
        found = line.find(this->_defaultDelimiter);
        tmp_gff.setSource(line.substr(0, found));
        line = line.substr(found+1);
       
        // the feature
        found = line.find(this->_defaultDelimiter);
        tmp_gff.setFeature(line.substr(0, found));
        line = line.substr(found+1);

        // the start
        found = line.find(this->_defaultDelimiter);
        tmp_gff.setStart(static_cast<unsigned int>(std::stoul(line.substr(0, found))));
        line = line.substr(found+1);
        
        // the end
        found = line.find(this->_defaultDelimiter);
        tmp_gff.setEnd(static_cast<unsigned int>(std::stoul(line.substr(0, found))));
        line = line.substr(found+1);
        
        // the score
        found = line.find(this->_defaultDelimiter);
        if (line.substr(0, found).compare(".") == 0) {
          tmp_gff.setScore();
        } else {
          tmp_gff.setScore(static_cast<double>(std::stod(line.substr(0, found))));
        }
        line = line.substr(found+1);
  
        
        // the strand
        found = line.find(this->_defaultDelimiter);
        if (line.substr(0, found).compare(".") == 0) {
          tmp_gff.setStrand();
        } else {
          tmp_gff.setStrand(static_cast<char>((line.substr(0, found)).c_str()[0]));

        }
        line = line.substr(found+1);
        
        // the frame
        found = line.find(this->_defaultDelimiter);
        
        // As the last attribute is optional it might be that the frame is the last value.
        if (found != std::string::npos) {
          if (line.substr(0, found).compare(".") == 0) {
            tmp_gff.setFrame();
          } else {
            tmp_gff.setFrame(static_cast<unsigned short>(std::stoul(line.substr(0, found))));
          }
          line = line.substr(found+1);
        } else {
          if (line.compare(".") == 0) {
            tmp_gff.setFrame();
          } else {
            tmp_gff.setFrame(static_cast<unsigned short>(std::stoul(line)));
          }
          tmp_gff.setAttribute_string();
          continue;
        }

        // If the string continous the attribute must be set.
        
        // For version 1 it is easy.
        if (this->_version == 1) {
          if (line.front() == '"' && line.back() == '"') {
            line.pop_back();
            line = line.substr(1);
            tmp_gff.setAttribute_string(line);
          }
        } else {
          // For the other versions a bit more effort must be done.
          found = std::string::npos;
          found = line.find(this->_attributeDelimiter);
          
          //go through the string and search for the delimiter
          
          while (found != std::string::npos) {
            
            std::string keyvalue = line.substr(0, found);
            
            // remove disturbing characters at front if there are some left
            if (keyvalue.front() == ' ')
              keyvalue = keyvalue.substr(1);
            if (keyvalue.front() == this->_attributeDelimiter)
              keyvalue = keyvalue.substr(1);
            if (keyvalue.front() == this->_keyValueDelimiter)
              keyvalue = keyvalue.substr(1);
            
            
            // extract key and value
            std::string key;
            std::string value;
            
            // starting with the key
            key = keyvalue.substr(0, keyvalue.find(this->_keyValueDelimiter));
    
            if (key.front() == ' ')
              key = key.substr(1);
            if (key.back() == ' ')
              key.pop_back();

            // continue with the value
            value = keyvalue.substr(keyvalue.find(this->_keyValueDelimiter));

            if (value.front() == ' ')
              value = value.substr(1);
            if (value.back() == ' ')
              value.pop_back();
            if (value.front() == '"' && value.back() == '"') {
              value.pop_back();
              value = value.substr(1);
            }

            tmp_gff.addAttribute(key, value);
            
            // reduce string
            // first chom all delimiters at front of line
            line = line.substr(found+1);
            
            found = line.find(this->_attributeDelimiter);
          }
            
          // get last element also
          if (line.empty() == false) {
            
            std::string keyvalue = line;
            
            // remove disturbing characters at front if there are some left
            if (keyvalue.front() == ' ')
              keyvalue = keyvalue.substr(1);
            if (keyvalue.front() == this->_attributeDelimiter)
              keyvalue = keyvalue.substr(1);
            if (keyvalue.front() == this->_keyValueDelimiter)
              keyvalue = keyvalue.substr(1);
            
            // extract key and value
            std::string key;
            std::string value;
            
            // starting with the key
            key = keyvalue.substr(0, keyvalue.find_first_of(this->_keyValueDelimiter));
            if (key.front() == ' ')
              key = key.substr(1);
            if (key.back() == ' ')
              key.pop_back();
            
            // continue with the value
            value = keyvalue.substr(keyvalue.find_first_of(this->_keyValueDelimiter));
            if (value.front() == ' ')
              value = value.substr(1);
            if (value.back() == ' ')
              value.pop_back();
            if (value.front() == '"' && value.back() == '"') {
              value.pop_back();
              value = value.substr(1);
            }
            
            tmp_gff.addAttribute(key, value);
          }
    
          // store extracted data
          data.push_back(tmp_gff);
        }
      }
      //datafile.close();
      
      std::cout << "Finished reading file: " << *this->_file << std::endl;
    
    } else {
        throw fs::Exception("Unable to open file: " + *this->_file);
    }
    
  } catch (fs::Exception &e) {
    std::cout << std::endl;
    std::cout << e.message() << std::endl;
    exit(1);
  }
}
  