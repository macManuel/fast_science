//
//  clapSingleArgument.cpp
//  fast_science
//
//
//  Created by Manuel on 20.06.15.
//

#include "clapSingleArgument.h"

template <class T>
fs::ClapSingleArgument<T>::ClapSingleArgument(fs::CommandlineParser & parser, std::string const & flag, std::string const & valueType, std::string const & description, bool isRequired, bool isSwitch) : ClapArgument(flag, description, isRequired, isSwitch) {
  
  _valueType = new std::string(valueType);
  
  _valueConstraints = nullptr;
  
  parser.addArgument(this);
}


template <class T>
fs::ClapSingleArgument<T>::ClapSingleArgument(fs::CommandlineParser & parser, std::string  const & flag, std::set<T> const & valueConstraints, std::string const & valueType, std::string const & description, bool isRequired, bool isSwitch) : ClapArgument(flag, description, isRequired, isSwitch) {
  
  _valueType = new std::string(valueType);
  
  _valueConstraints = new std::set<T>(valueConstraints);
  
  parser.addArgument(this);
}


template <>
fs::ClapSingleArgument<bool>::ClapSingleArgument(fs::CommandlineParser & parser, char const & flag, std::string const & valueType, std::string const & description, bool isRequired, bool isSwitch) : ClapArgument(flag, description, isRequired, isSwitch) {
  
  _valueType = new std::string(valueType);
  
  _valueConstraints = new std::set<bool>();
  _valueConstraints->insert(true);
  _valueConstraints->insert(false);
  
  parser.addArgument(this);
}


template <class T>
fs::ClapSingleArgument<T>::~ClapSingleArgument() {
  
  if (_valueType != nullptr) {
    delete _valueType;
    _valueType = nullptr;
  }
  
  if (_valueConstraints != nullptr) {
    delete _valueConstraints;
    _valueConstraints = nullptr;
  }
}



template <class T>
T const & fs::ClapSingleArgument<T>::value() const {
  return *_value;
}


template <class T>
void fs::ClapSingleArgument<T>::setValue(std::string const & valueRead) {
  
  T toSet;
  
  std::istringstream is(valueRead);
  
  int valuesRead = 0;
  while ( is.good() ) {
    if ( is.peek() != EOF )
      
    is >> toSet;
    
    valuesRead++;
  }

  if (isValid(toSet)) {
    _value = new T(toSet);
  }
}



template <class T>
bool fs::ClapSingleArgument<T>::isValid(T const & value) const {
  
  
  // first check if the _value is still empty
  
  if (_value != nullptr) {
    throw fs::Exception("Argument already set: " + *_flag);
    return false;
  }
  
  // check only if there were restrictions given
  if (_valueConstraints != nullptr) {
    
    // count how often the value is appears in the constrint set.
    // Should be one if everything is all right and 0 otherwise.
    unsigned long counter = _valueConstraints->count(*_value);
    
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