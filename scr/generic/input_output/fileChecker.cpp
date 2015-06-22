//
//  fileChecker.cpp
//  fast_science
//
//
//  Created by Manuel on 12.06.15.
//
//

#include "fileChecker.h"


fs::FileChecker::FileChecker() {
  this->_isCsv = false;
  this->_isGff = false;
  this->_isBedgraph = false;
  this->_isWig = false;
}


fs::FileChecker::~FileChecker() {
  
}



bool fs::FileChecker::isCsv() const {
  return this->_isCsv;
}


bool fs::FileChecker::isGff() const {
  return this->_isGff;
}


bool fs::FileChecker::isBedgraph() const {
  return this->_isBedgraph;
}


bool fs::FileChecker::isWig() const {
   return this->_isWig;
}



void fs::FileChecker::check(std::string const & file) {
  
  std::string suffix;
  std::size_t found = file.find_last_of('.');
  if (found == std::string::npos) {
  
    // if there is no suffix
  } else {
    
    suffix = file.substr(found+1);
    fs::lowercase_string (suffix);

    if (suffix.compare("csv") == 0) {
      this->_isCsv = true;
    }
    
    if (suffix.compare("gff") == 0 || suffix.compare("gft") == 0) {
      this->_isGff = true;
    }
    
    if (suffix.compare("bedgraph") == 0) {
      this->_isBedgraph = true;
    }
    
    if (suffix.compare("wig") == 0) {
      this->_isWig = true;
    }
  }
}

  
