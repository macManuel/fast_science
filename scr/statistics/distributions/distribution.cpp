//
//  distribution.cpp
//  fast_science
//
//
//  Created by Manuel on 20.06.15.
//
//

#include "distribution.h"

fs::Distribution::Distribution() {
  this->_elements = new std::vector<double>;
}

fs::Distribution::Distribution(std::vector<double> const & element) {
 
  this->_elements = new std::vector<double>(element);
}


fs::Distribution::~Distribution() {
  
  delete this->_elements;
  this->_elements = nullptr;
}


void fs::Distribution::addElement(double element) {
  
  this->_elements->push_back(element);
}



double fs::Distribution::quantile(double p) {
  // first sort the list of elements.
  std::sort(this->_elements->begin(), this->_elements->end());
  
  if (p <= 0) {
    return this->_elements->front();
  }
  
  if (p >= 1) {
    return this->_elements->back();
  }
  
  // Calcuate the number of values in the quantile. Return always a value which is definetely part of that quantile.
  // If n*p is even, return the middle between x[n*p] and x[n*(p+1)]. Else return the value x[>n*p.]
  
  unsigned long ith_value = this->_elements->size() * p;
  bool is_even = false;
  
  if ( ith_value % 2 == 0) {
    is_even = true;
  }
  
  
  if (is_even == true) {
    return ((this->_elements->at(ith_value) + this->_elements->at(ith_value + 1) ) / 2);
  } else {
    return (this->_elements->at(ith_value + 1));
  }
}
      
