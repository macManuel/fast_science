//
//  clapArgument.cpp
//  fast_science
//
//
//  Created by Manuel on 20.06.15.
//

#include "clapArgument.h"


fs::ClapArgument::ClapArgument(std::string const & flag, std::string const & description, bool isRequired, bool isSwitch) {
  
  _flag = new std::string(flag);
  
  _hyphen = new std::string("--");
  
  _description = new std::string(description);
  
  _isRequired = isRequired;
  
  _isSwitch = isSwitch;
  
  
}



fs::ClapArgument::ClapArgument(char flag, std::string const & description, bool isRequired, bool isSwitch) {
  
  _flag = new std::string(1, flag);
  
  _hyphen = new std::string("--");
  
  _description = new std::string(description);
  
  _isSwitch = isSwitch;
  
  _isRequired = isRequired;
}



fs::ClapArgument::~ClapArgument() {
  
  if (_flag != nullptr) {
    delete _flag;
    _flag = nullptr;
  }
  
  if (_hyphen != nullptr) {
    delete _hyphen;
    _hyphen = nullptr;
  }
  
  if (_description != nullptr) {
    delete _description;
    _description = nullptr;
  }
  
}



std::string const & fs::ClapArgument::flag() const {
  return *_flag;
};



std::string const & fs::ClapArgument::hyphen() const {
  return *_hyphen;
}



bool fs::ClapArgument::isRequired() const {
  return _isRequired;
}



bool fs::ClapArgument::isSwitch() const {
  return _isSwitch;
}



std::string const & fs::ClapArgument::description() const {
  return *_description;
}


