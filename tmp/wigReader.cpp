//
//  wigReader.cpp
//  fast_science
//
//
//  Created by Manuel on 20.06.15.
//
//


#include "WigReader.h"

void fs::WigReader::WigInit() {
  
  // all .wig files have the same delimiters
  this->_defaultDelimiter = '\t';
}



fs::WigReader::WigReader(std::string const & file, std::string const & path) : fs::Reader<fs::BedgraphFormat>(file, path) {
  
  WigInit();
}

fs::WigReader::WigReader(std::string const & fileWithPath) : fs::Reader<fs::BedgraphFormat>(fileWithPath) {
  
  WigInit();
}

fs::WigReader::~WigReader() {
  
}


void fs::WigReader::readFromFile(std::list<fs::BedgraphFormat> & data) {

  // open the file
  std::fstream datafile;
  
  try {
    datafile.open(*(this->_path) + *(this->_file) + *(this->_suffix), std::fstream::in | std::fstream::binary);
    
    if (datafile.is_open()){
      
      // define some temporary varaibles
      std::string line;
      
      bool variable_step = true;
      std::string chromosome;
      unsigned int span = 1;
      unsigned int start = 0;
      unsigned int step = 1;
      
      
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
        if (line.find_last_of('\n') == line.length())
          line.pop_back();
        while (line.back() == this->_defaultDelimiter) {
          line.pop_back();
        }
        

        // third, figure out if the line is a declaration line
        // if so see wheather we have a variable or fixed step format
        std::size_t found = std::string::npos;
        
        if (string_contains_string(line, "chrom")) {
          // must be a declaration line
          
          if (string_contains_string(line, "variableStep") ){
            // variable steps:
            variable_step = true;
          } else {
            variable_step = false;
          }
          
          
          // extract all relevant information from declaration line.
          found = line.find(this->_defaultDelimiter);
          line = line.substr(found+1);
            
          // chromosome
          found = line.find("chrom=");
          line = line.substr(found+1);
          found = line.find(_defaultDelimiter);
          // if line is not yet finished
          if (found != std::string::npos) {
            chromosome = line.substr(0, found);
          } else {
            chromosome = line;
            continue;
          }
          
          
          //start
          found = line.find("start=");
          if (found != std::string::npos) {
            line = line.substr(found+1);
            found = line.find(this->_defaultDelimiter);
            start = static_cast<unsigned int>(std::stoul(line.substr(0, found)));
          }
          
          //step
          found = line.find("step=");
          if (found != std::string::npos) {
            line = line.substr(found+1);
            found = line.find(this->_defaultDelimiter);
            // if line is not yet finished
            if (found != std::string::npos) {
              step = static_cast<unsigned int>(std::stoul(line.substr(0, found)));
            } else {
              step = static_cast<unsigned int>(std::stoul(line));
              continue;
            }
          }
          
          // span
          found = line.find("span=");
          if (found != std::string::npos) {
            line = line.substr(found+1);
            span = static_cast<unsigned int>(std::stoul(line.substr(0, found)));
            continue;
          }
        }
        
        
        // otherwise store data in the data list
        fs::BedgraphFormat tmp_bedgraph;
        
        tmp_bedgraph.setChrom(chromosome);
        
        // for variable data
        if (variable_step) {
          tmp_bedgraph.setChromStart(static_cast<unsigned int>(std::stoul(line.substr(0, found))));
          tmp_bedgraph.setChromEnd(static_cast<unsigned int>(std::stoul(line.substr(0, found)))+span);
          line = line.substr(found+1);
          tmp_bedgraph.setScore(std::stod(line));
          
          // for fixed step
        } else {
          tmp_bedgraph.setChromStart(start);
          tmp_bedgraph.setChromEnd(start+span);
          start += step;
          
          tmp_bedgraph.setScore(std::stod(line));
        }
        
        // finally store the object in the data list
        data.push_back(tmp_bedgraph);
      }
      datafile.close();
      std::cout << "Finished reading file: " << *this->_file << std::endl;
    } else {
      throw fs::Exception("Unable to open file: " + *this->_file);
    }
    
    } catch (fs::Exception &e) {
      std::cout << e.message() << std::endl;
      exit(1);
    }
}



