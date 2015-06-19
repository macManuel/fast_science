//
//  exception.cpp
//  fast_science
//
//
//  Created by Manuel on 20.06.15.
//
//

#include "exception.h"

fs::Exception::Exception(std::string const & message) {
  
  _message = new std::string (message);
}


fs::Exception::~Exception() {
  if (_message != nullptr) {
    delete _message;
    _message = nullptr;
  }
}


std::string const & fs::Exception::message() const {
  return *_message;
}

