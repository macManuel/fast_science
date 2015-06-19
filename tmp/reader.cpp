//
//  reader.cpp
//  fast_science
//
//
//  Created by Manuel on 12.06.15.
//
//

#include "reader.h"

template <class T>
fs::Reader<T>::Reader(std::string const & file, std::string const & path) {
  
  _suffix = new std::string;
  _file = new std::string;
  _path = new std::string;
  
  std::string tmp_str = file;
  // look for the suffix in the filename
  std::size_t found = tmp_str.find_last_of('.');
  if (found != std::string::npos) {
    *_suffix = tmp_str.substr(found);
    *_file = tmp_str.substr(0, found);
  } else {
    *_file = file;
  }
  
  // make sure the file does not start with a '/'
  if (_file->front() == '/') {
      *_file = _file->substr(1);
    }

  *_path = path;
  // make sure the path ends with a '/'
  if (! path.empty()) {
    if (_path->back() != '/') {
    	_path->push_back('/');
    }
  }

  _comment = new std::vector<std::string> {"#", "//" ,"/*", "%"};
}
  

template <class T>
fs::Reader<T>::Reader(std::string const & fileWithPath) {

  _suffix = new std::string;
  _file = new std::string;
  _path = new std::string;
  
  std::string tmp_str = fileWithPath;
  
	// first set the path correctly
  std::size_t found = tmp_str.find_last_of("/");
  if (found != std::string::npos) {
    *_path = tmp_str.substr(0,found);
    if (_path->back() != '/') {
      _path->push_back('/');
  	}
  } else {
     *_path = "";
  }
  
  // now set the suffix and filename
  if (found != std::string::npos) {
    tmp_str = tmp_str.substr(found);
  }
  
  // look for the suffix in the filename
  found = tmp_str.find_last_of('.');
  if (found != std::string::npos) {
    *_suffix = tmp_str.substr(found);
    *_file = tmp_str.substr(0, found);
  } else {
    *_file = tmp_str;
    *_suffix = "";
    
  }
  
  // make sure the file does not start with a '/'
  if (_file->front() == '/') {
    *_file = _file->substr(1);
  }
  _comment = new std::vector<std::string> {"#", "//" ,"/*", "%"};
  
}


template <class T>
fs::Reader<T>::~Reader() {
  
  delete _suffix;
  _suffix = nullptr;
  
  delete _file;
  _file = nullptr;
  
  delete _path;
  _path = nullptr;
  
  delete _comment;
  _comment = nullptr;
}


template <class T>
std::string const & fs::Reader<T>::path() const {
  return *this->_path;
}

template <class T>
std::string const & fs::Reader<T>::file() const {
  return *this->_file;
}

template <class T>
std::string const & fs::Reader<T>::suffix() const {
  return *this->_suffix;
}



// instantiate those types which can be used
template class fs::Reader<fs::CsvFormat<unsigned short>>;
template class fs::Reader<fs::CsvFormat<short>>;
template class fs::Reader<fs::CsvFormat<unsigned int>>;
template class fs::Reader<fs::CsvFormat<int>>;
template class fs::Reader<fs::CsvFormat<unsigned long>>;
template class fs::Reader<fs::CsvFormat<long>>;
template class fs::Reader<fs::CsvFormat<float>>;
template class fs::Reader<fs::CsvFormat<double>>;

template class fs::Reader<fs::CsvFormat<std::string>>;
template class fs::Reader<fs::GffFormat>;
template class fs::Reader<fs::BedgraphFormat>;
