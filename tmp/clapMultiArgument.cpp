//
//  clapMultiArgument.h
//  fast_science
//
//
//  Created by Manuel on 20.06.15.
//

#include "clapMultiArgument.h"

template <typename T>
fs::ClapMultiArgument<T>::ClapMultiArgument(fs::CommandlineParser & parser, std::string const & flag, std::string const &  usageDescription, std::string const &  longDescription, bool isRequired, bool isSwitch) : ClapArgument(flag, usageDescription, longDescription, isRequired, isSwitch) {
  
  _value = new std::vector<T>;
  _valueConstraints = new std::set<T>();
  
  parser.addArgument(this);
}


template <typename T>
fs::ClapMultiArgument<T>::ClapMultiArgument(fs::CommandlineParser & parser, std::string  const & flag, std::set<T> const & valueConstraints, std::string const &  usageDescription, std::string const &  longDescription, bool isRequired, bool isSwitch) : ClapArgument(flag, usageDescription, longDescription, isRequired, isSwitch) {
  
  _value = new std::vector<T>;
  _valueConstraints = new std::set<T>(valueConstraints);
  parser.addArgument(this);
}


template <>
fs::ClapMultiArgument<bool>::ClapMultiArgument(fs::CommandlineParser & parser, char const & flag, std::string const &  usageDescription, std::string const &  longDescription, bool isRequired, bool isSwitch) : ClapArgument(flag, usageDescription, longDescription, isRequired, isSwitch) {
  
  _value = new std::vector<bool>;
  
  _valueConstraints = new std::set<bool>();
  _valueConstraints->insert(true);
  _valueConstraints->insert(false);
  
  parser.addArgument(this);
}


template <typename T>
fs::ClapMultiArgument<T>::~ClapMultiArgument() {
  
  delete _value;
  _value = nullptr;
  
  delete _valueConstraints;
  _valueConstraints = nullptr;
}



template <typename T>
std::vector<T> const & fs::ClapMultiArgument<T>::value() const {
  return *_value;
}



template <typename T>
void fs::ClapMultiArgument<T>::setValue(std::string const & valueRead) {
  
  T toSet;
  
  std::istringstream is(valueRead);
  
  int valuesSet = 0;
  while ( is.good() ) {
    if ( is.peek() != EOF )
      
      is >> toSet;
    
    if (isValid(toSet)) {
      this->_value->push_back(toSet);
      this->_isSet = true;
      valuesSet++;
    }
  }
}



template <typename T>
bool fs::ClapMultiArgument<T>::isValid(T const & value) const {
  
  
  // check only if there were restrictions given
  if (_valueConstraints->empty() == false) {
    
    // count how often the value appears in the constrint set.
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

template class fs::ClapMultiArgument<bool>;
template class fs::ClapMultiArgument<char>;
template class fs::ClapMultiArgument<unsigned short>;
template class fs::ClapMultiArgument<short>;
template class fs::ClapMultiArgument<unsigned int>;
template class fs::ClapMultiArgument<int>;
template class fs::ClapMultiArgument<unsigned long>;
template class fs::ClapMultiArgument<long>;
template class fs::ClapMultiArgument<unsigned long long>;
template class fs::ClapMultiArgument<long long>;
template class fs::ClapMultiArgument<float>;
template class fs::ClapMultiArgument<double>;

template class fs::ClapMultiArgument<std::string>;