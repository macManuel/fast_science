//
//  csvWriter.cpp
//  fast_science
//
//
//  Created by Manuel on 20.06.15.
//
//

#include "csvWriter.h"
template <typename T>
fs::CsvWriter<T>::CsvWriter(std::string const & file, std::string const & path, char delimiter) : Writer<fs::CsvFormat<T>>(file, path){
  
  this->_delimiter = delimiter;
  
  // set the suffix if none is given.
  if (this->_suffix->empty() == true) {
    *this->_suffix = ".csv";
  }
}


template <typename T>
fs::CsvWriter<T>::CsvWriter(std::string const & fileWithPath, char delimiter) : Writer<fs::CsvFormat<T>>(fileWithPath) {
  
  
  this->_delimiter = delimiter;
  
  // set the suffix if none is given.
  if (this->_suffix->empty() == true) {
    *this->_suffix = ".csv";
  }
}


template <typename T>
fs::CsvWriter<T>::~CsvWriter() {

}


template <typename T>
void fs::CsvWriter<T>::writeIntoFile(std::list<fs::CsvFormat<T>> const & data) {
  
  try {
    
    // open the file
    std::fstream datafile;
    
    datafile.open(*(this->_path) + *(this->_file) + *(this->_suffix), std::fstream::out | std::fstream::binary);
    
    if (datafile.is_open()){
      
      
      for (auto it = data.begin(); it != data.end(); ++it) {
        for (auto jt = it->aline().cbegin(); jt != it->aline().cend(); ++jt) {
          
          // wite out directly to file
          datafile << *jt;
          
          // check if this was the last element
          auto tmp = jt;
          ++tmp;
          if (tmp == it->aline().cend()) {
            continue;
          }
          
          // if not write out a delimiter
          datafile << this->_delimiter;
        }
        
        // and a end line character at the end
        datafile << "\n";
      }
      
      datafile.close();
      std::cout << "Finished writing file: " << *this->_file << std::endl;
    } else {
      throw fs::Exception("Unable to open file: " + *this->_file);
    }
    
  } catch (fs::Exception &e) {
    std::cout << e.message() << std::endl;
    exit(1);
  }
}



// instantiate those types which can be used
template class fs::CsvWriter<short>;
template class fs::CsvWriter<unsigned short>;
template class fs::CsvWriter<int>;
template class fs::CsvWriter<unsigned int>;
template class fs::CsvWriter<long>;
template class fs::CsvWriter<unsigned long>;
template class fs::CsvWriter<float>;
template class fs::CsvWriter<double>;
template class fs::CsvWriter<std::string>;
