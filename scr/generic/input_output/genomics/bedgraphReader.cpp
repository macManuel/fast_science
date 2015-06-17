//
//  bedgraohReader.cpp
//  fast_science
//
//
//  Created by Manuel on 20.06.15.
//
//

#include "bedgraphReader.h"

void fs::BedgraphReader::BedgraphInit() {
  
  // all .bedgraph files have the same delimiters
  this->_defaultDelimiter = '\t';
}


fs::BedgraphReader::BedgraphReader(std::string const & file, std::string const & path) : fs::Reader<fs::BedgraphFormat>(file, path) {
  
  BedgraphInit();
}

fs::BedgraphReader::BedgraphReader(std::string const & fileWithPath) : fs::Reader<fs::BedgraphFormat>(fileWithPath) {
  
  BedgraphInit();
}

fs::BedgraphReader::~BedgraphReader() {
}

void fs::BedgraphReader::readFromFile(std::list<fs::BedgraphFormat> & data) {
  
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
        if (line.find_last_of('\n') == line.length())
          line.pop_back();
        if (line.find_last_of(this->_defaultDelimiter) == line.length())
          line.pop_back();

        
        // third, check for each liner if ther are at least 3 values
        unsigned int counter = std::count (line.begin(), line.end(), this->_defaultDelimiter);
        if (counter < 3) {
          // This should not happen!
          throw fs::Exception("Unvalide string: \"" + line + "\" at line: " + std::to_string(line_counter));
        }
        
        
        // now split the line at every delimiter and store the elements in the GFF object;
        fs::BedgraphFormat tmp_bedgraph;
        std::size_t found = std::string::npos;
        
        // the chromosome
        found = line.find(this->_defaultDelimiter);
        tmp_bedgraph.setChrom(line.substr(0, found));
        line = line.substr(found+1);
        
        // the start
        found = line.find(this->_defaultDelimiter);
        tmp_bedgraph.setChromStart(static_cast<unsigned int>(std::stoul(line.substr(0, found))));
        line = line.substr(found+1);
        
        // the end
        found = line.find(this->_defaultDelimiter);
        tmp_bedgraph.setChromEnd(static_cast<unsigned int>(std::stoul(line.substr(0, found))));
        line = line.substr(found+1);
        
        // the score
        tmp_bedgraph.setScore(static_cast<double>(std::stod(line)));
        
        // store extracted data
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