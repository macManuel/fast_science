//
//  csvFormat.cpp
//  fast_science
//
//
//  Created by Manuel on 20.06.15.
//
//

#include "csvFormat.h"

template <class T>
fs::CsvFormat<T>::CsvFormat() {
  
}

template <class T>
fs::CsvFormat<T>::CsvFormat(std::list<T> const & line) {
  
  _aline = new std::list<T>(line);
}


template <class T>
fs::CsvFormat<T>::CsvFormat(const CsvFormat& original) {
  
    _aline = new std::list<T>(original.aline());
}


template <class T>
fs::CsvFormat<T>& fs::CsvFormat<T>::operator= (const CsvFormat& original) {
  
  if (&original != this) {
      _aline = new std::list<T>(original.aline());
  }
  return *this;
}


template <class T>
fs::CsvFormat<T>::~CsvFormat() {
  
  delete _aline;
  _aline = nullptr;
}


template <class T>
std::list<T> const & fs::CsvFormat<T>::aline() const {
  return *_aline;
}


template <class T>
void fs::CsvFormat<T>::setAline(std::list<T> const & aline) {
  
  *_aline = aline;
}


template <class T>
void fs::CsvFormat<T>::addToAline(T const & toAdd) {
 
  _aline->push_back(toAdd);
  
}


// instantiate those types which can be used
template class fs::CsvFormat<unsigned short>;
template class fs::CsvFormat<short>;
template class fs::CsvFormat<unsigned int>;
template class fs::CsvFormat<int>;
template class fs::CsvFormat<unsigned long>;
template class fs::CsvFormat<long>;
template class fs::CsvFormat<float>;
template class fs::CsvFormat<double>;

template class fs::CsvFormat<std::string>;



