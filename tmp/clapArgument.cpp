//
//  clapArgument.cpp
//  fast_science
//
//
//  Created by Manuel on 20.06.15.
//

#include "clapArgument.h"


fs::ClapArgument::ClapArgument(std::string const & flag, std::string const & usageDescription, std::string const & longDescription, bool isRequired, bool isSwitch) {
  
  _flag = new std::string(flag);
  _hyphen = new std::string("--");
  _longDescription = new std::string(longDescription);
  _usageDescription = new std::string(usageDescription);
  _isRequired = isRequired;
  _isSwitch = isSwitch;
  _isSet = false;
}



fs::ClapArgument::ClapArgument(char flag, std::string const & usageDescription, std::string const & longDescription, bool isRequired, bool isSwitch) {
  
  _flag = new std::string;
  _flag->push_back(flag);
  _hyphen = new std::string("-");
  _longDescription = new std::string(longDescription);
  _usageDescription = new std::string(usageDescription);
  _isRequired = isRequired;
  _isSwitch = isSwitch;
  _isSet = false;
}



fs::ClapArgument::~ClapArgument() {
  
  delete _flag;
  _flag = nullptr;
  
  delete _hyphen;
  _hyphen = nullptr;
  
  delete _longDescription;
  _longDescription = nullptr;
  
  delete _usageDescription;
  _usageDescription = nullptr;
  
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


bool fs::ClapArgument::isSet() const {
  return _isSet;
}


std::string const & fs::ClapArgument::longDescription() const {
  return *_longDescription;
}

std::string const & fs::ClapArgument::usageDescription() const {
  return *_usageDescription;
}


