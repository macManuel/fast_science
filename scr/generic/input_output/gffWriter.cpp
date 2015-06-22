//
//  csvWriter.cpp
//  fast_science
//
//
//  Created by Manuel on 20.06.15.
//
//

#include "gffWriter.h"

fs::GffWriter::GffWriter(std::string const & file, std::string const & path, unsigned short version) : Writer<fs::GffFormat>(file, path){
  
  // every .ggf file has the same delimiters.
  this->_delimiter = '\t';
  this->_attributeDelimiter = ';';
  
  // first check if the user wants a gtf file, which means the version must be 2
  if (this->_suffix->compare(".gtf") == 0) {
    this->_version = 2;
  } else {
    if (version < 3) {
      this->_version = version;
    } else {
      this->_version = 3;
    }
    
    *this->_suffix = ".gff";
  }
  
  // set the attribute delimiter for versions > 1
  if (this->_version == 2) {
    this->_keyValueDelimiter = ' ';
  }
  if (this->_version == 3) {
    this->_keyValueDelimiter = '=';
  }
}


fs::GffWriter::GffWriter(std::string const & fileWithPath, unsigned short version) : Writer<fs::GffFormat>(fileWithPath) {
  
  // every .ggf file has the same delimiters.
  this->_delimiter = '\t';
  this->_attributeDelimiter = ';';
  
  // first check if the user wants a gtf file, which means the version must be 2
  if (this->_suffix->compare(".gtf") == 0) {
    this->_version = 2;
  } else {
    if (version < 3) {
      this->_version = version;
    } else {
      this->_version = 3;
    }
    
    *this->_suffix = ".gff";
  }
  
  // set the attribute delimiter for versions > 1
  if (this->_version == 2) {
    this->_keyValueDelimiter = ' ';
  }
  if (this->_version == 3) {
    this->_keyValueDelimiter = '=';
  }
}


fs::GffWriter::~GffWriter() {
  
}


void fs::GffWriter::writeIntoFile(std::list<fs::GffFormat> const & data) {
  
  try {
    // open the file
    std::fstream datafile;
    
    datafile.open(*(this->_path) + *(this->_file) + *(this->_suffix), std::fstream::out | std::fstream::binary);
    
    if (datafile.is_open()){
      
      for (auto it = data.begin(); it != data.end(); ++it) {
        
        // wite out one value after another
        
        // the seqname
        datafile << it->seqname() << this->_delimiter;
        
        // the source
        datafile << it->source() << this->_delimiter;
        
        // the featur
        datafile << it->feature() << this->_delimiter;
        
        // the start
        datafile << it->start() << this->_delimiter;
        
        // the end
        datafile << it->end() << this->_delimiter;
        
        // the score
        if (it->hasScore() == true) {
          datafile << it->score() << this->_delimiter;
        } else {
          datafile << "." << this->_delimiter;
        }
        
        // the strand
        if (it->hasStrand() == true) {
          datafile << it->strand() << this->_delimiter;
        } else {
          datafile << "." << this->_delimiter;
        }
        
        // the frame
        if (it->hasFrame() == true) {
          datafile << it->frame() << this->_delimiter;
        } else {
          datafile << ".";
        }
        
        // the attribute if available
        if (it->hasAttribute_string() == true) {
          datafile << this->_delimiter << it->attribute_string();
          continue;
        } else if (it->hasAttribute_string() == false && it->hasAttribute_map() == false){
          continue;
        } else {
          
          // go through all attributes
          for (auto jt = it->attribute_map().cbegin(); jt != it->attribute_map().cend(); ++jt) {
            datafile << this->_delimiter;
            datafile << jt->first << this->_keyValueDelimiter;
            
            // now depending on the fact if we have output in version 2 or three
            if (this->_version == 2) {
              datafile << "\"" << jt->second << "\"";
            } else {
              datafile << jt->second;
            }
            // check if this was the last element
            auto tmp = jt;
            ++tmp;
              if (tmp == it->attribute_map().cend()) {
                continue;
              }
            
            // if not write out a delimiter
            datafile << this->_attributeDelimiter;
          }
        }
        // and a end line character at the end
        datafile << "\n";
      }
      
      datafile.close();
      std::cout << "Finished writing file: " << *this->_file << std::endl;
    } else {
      throw fs::Exception("Unable to open file: " + *this->_file);
    }
    
  } catch (fs::Exception &e) {
    std::cout << e.message() << std::endl;
    exit(1);
  }
}


  
  
  
  
