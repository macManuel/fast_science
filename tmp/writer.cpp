//
//  writer.cpp
//  fast_science
//
//
//  Created by Manuel on 12.06.15.
//
//

#include "writer.h"

template <typename T>
fs::Writer<T>::Writer(std::string const & file, std::string const & path) {
  
  _path = new std::string;
  _file = new std::string;
  _suffix = new std::string;
  
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
}


template <class T>
fs::Writer<T>::Writer(std::string const & fileWithPath) {

  _path = new std::string;
  _file = new std::string;
  _suffix = new std::string;
  
  std::string tmp_str = fileWithPath;
  
  // first set the path correctly
  std::size_t found = tmp_str.find_last_of('/');
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
}


template <typename T>
fs::Writer<T>::~Writer() {
  
  delete _file;
  _file = nullptr;
  
  delete _path;
  _path = nullptr;
}


template class fs::Writer<fs::CsvFormat<unsigned short>>;
template class fs::Writer<fs::CsvFormat<short>>;
template class fs::Writer<fs::CsvFormat<unsigned int>>;
template class fs::Writer<fs::CsvFormat<int>>;
template class fs::Writer<fs::CsvFormat<unsigned long>>;
template class fs::Writer<fs::CsvFormat<long>>;
template class fs::Writer<fs::CsvFormat<float>>;
template class fs::Writer<fs::CsvFormat<double>>;

template class fs::Writer<fs::CsvFormat<std::string>>;
template class fs::Writer<fs::GffFormat>;
template class fs::Writer<fs::BedgraphFormat>;