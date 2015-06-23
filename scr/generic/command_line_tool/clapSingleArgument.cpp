//
//  clapSingleArgument.cpp
//  fast_science
//
//
//  Created by Manuel on 20.06.15.
//

#include "clapSingleArgument.h"

template <class T>
fs::ClapSingleArgument<T>::ClapSingleArgument(fs::CommandlineParser & parser, std::string const & flag, std::string const & usageDescription, std::string const & longDescription, bool isRequired, bool isSwitch) : ClapArgument(flag, usageDescription, longDescription, isRequired, isSwitch) {
  
  _value = new T;
  _valueConstraints = new std::set<T>();
  parser.addArgument(this);
}


template <class T>
fs::ClapSingleArgument<T>::ClapSingleArgument(fs::CommandlineParser & parser, std::string  const & flag, std::set<T> const & valueConstraints, std::string const & usageDescription, std::string const & longDescription, bool isRequired, bool isSwitch) : ClapArgument(flag, usageDescription, longDescription, isRequired, isSwitch) {
  
  _value = new T;
  _valueConstraints = new std::set<T>(valueConstraints);
  parser.addArgument(this);
}


template <>
fs::ClapSingleArgument<bool>::ClapSingleArgument(fs::CommandlineParser & parser, char const & flag, std::string const & usageDescription, std::string const & longDescription, bool isRequired, bool isSwitch) : ClapArgument(flag, usageDescription, longDescription, isRequired, isSwitch) {
  
  _value = new bool(false);
  
  _valueConstraints = new std::set<bool>();
  _valueConstraints->insert(true);
  _valueConstraints->insert(false);
  
  parser.addArgument(this);
}


template <class T>
fs::ClapSingleArgument<T>::~ClapSingleArgument() {
  
  delete _value;
  _value = nullptr;
  
  delete _valueConstraints;
  _valueConstraints = nullptr;
}



template <class T>
T const & fs::ClapSingleArgument<T>::value() const {
  return *_value;
}


template <class T>
void fs::ClapSingleArgument<T>::setValue(std::string const & valueRead) {
  
  T toSet;
  
  std::istringstream is(valueRead);
  
  while ( is.good() ) {
    if ( is.peek() != EOF ) {
      
      is >> toSet;
    }

    if (isValid(toSet)) {
      *this->_value = toSet;
    }

    this->_isSet = true;
  }
}



template <class T>
bool fs::ClapSingleArgument<T>::isValid(T const & value) const {
  
  
  // first check if the _value is still empty
  if (isSet() == true) {
    throw fs::Exception("Argument already set: " + *_flag);
    return false;
  }
  
  // check only if there were restrictions given
  if (_valueConstraints->empty() == false) {
    
    // count how often the value is appears in the constrint set.
    // Should be one if everything is all right and 0 otherwise.
    unsigned long counter = _valueConstraints->count(value);
    
    if (counter < 1) {
      throw fs::Exception("Invalid Argument for: " + *_flag);
      return false;
    }
  }
  return true;
}



// instantiate those types which can be used
template class fs::ClapSingleArgument<bool>;
template class fs::ClapSingleArgument<char>;
template class fs::ClapSingleArgument<unsigned short>;
template class fs::ClapSingleArgument<short>;
template class fs::ClapSingleArgument<unsigned int>;
template class fs::ClapSingleArgument<int>;
template class fs::ClapSingleArgument<unsigned long>;
template class fs::ClapSingleArgument<long>;
template class fs::ClapSingleArgument<unsigned long long>;
template class fs::ClapSingleArgument<long long>;
template class fs::ClapSingleArgument<float>;
template class fs::ClapSingleArgument<double>;

template class fs::ClapSingleArgument<std::string>;