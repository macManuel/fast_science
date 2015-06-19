//  csvReader.cpp
//  fast_science
//
//
//  Created by Manuel on 20.06.15.
//
//

#include "csvReader.h"

template <typename T>
void fs::CsvReader<T>::CsvInit() {
  
  _delimiters = new std::map<char ,unsigned int>({ {'\t',0}, {';',0}, {' ',0}, {',',0}, {':',0}, {'.',0} });
  
}

template <typename T>
fs::CsvReader<T>::CsvReader(std::string const & file, std::string const & path) : fs::Reader<CsvFormat<T>>(file, path) {
  
  CsvInit();
  _hasDefaultDelimiter = false;
  
}

template <typename T>
fs::CsvReader<T>::CsvReader(std::string const & file, std::string const & path, char delimiter) : fs::Reader<CsvFormat<T>>(file, path) {
  
  CsvInit();
  this->_defaultDelimiter = delimiter;
  _hasDefaultDelimiter = true;
}

template <typename T>
fs::CsvReader<T>::CsvReader(std::string const & fileWithPath)  : fs::Reader<CsvFormat<T>>(fileWithPath) {
  
  CsvInit();
  _hasDefaultDelimiter = false;
}

template <typename T>
fs::CsvReader<T>::CsvReader(std::string const & fileWithPath, char delimiter)  : fs::Reader<CsvFormat<T>>(fileWithPath) {
  
  CsvInit();
  this->_defaultDelimiter = delimiter;
  _hasDefaultDelimiter = true;
}

template <typename T>
fs::CsvReader<T>::~CsvReader() {
  
  delete _delimiters;
  _delimiters = nullptr;
}

template <typename T>
void fs::CsvReader<T>::readFromFile(std::list<CsvFormat<T>> & data) {

  // open the file
  std::fstream datafile;
  try {
    datafile.open(*(this->_path) + *(this->_file) + *(this->_suffix), std::fstream::in | std::fstream::binary);
   
    if (datafile.is_open()){
      
      std::string line;
      std::size_t found = std::string::npos;
      
      // go through each line
      unsigned int line_counter = 0;

      while (getline (datafile,line)) {
        ++line_counter;
             // first chomp all lines which are maked as comments
        
        std::string first_two = line.substr(0,2);
        
        bool comment = false;
        
        for ( auto it = this->_comment->cbegin(); it != this->_comment->end(); ++it ) {
          if (string_contains_string(first_two, *it)) {
            comment = true;
          }
        }
        
        if (comment == true) {
          continue;
        }
        
        
        // if no delimiter was given get first line and figure out which delimiter is used.
        if (_hasDefaultDelimiter == false) {
          
          // go through the first line string and try to figure out the delimiter by counting its occurence: Otherwise a user interaction is required.
          
          for (auto it = _delimiters->begin(); it != _delimiters->end(); ++it) {
            
            unsigned int counter = std::count (line.begin(), line.end(), it->first);
            it->second = counter;
          }

          
          // now see which delimiter is highest;
          std::pair<char, int> first_highest = {'0',0};
          std::pair<char, int> second_highest = {'0',0};
         
          for (auto it = _delimiters->cbegin(); it != _delimiters->cend(); ++it) {
            
            if (it->second > first_highest.second ) {
              first_highest.first = it->first;
              first_highest.second = it->second;
            } else if (it->second > second_highest.second ) {
              second_highest.first = it->first;
              second_highest.second = it->second;
            }
          }
          
          
          // if a delimiter was found set this as the default one.
          if (first_highest.first != second_highest.first) {
            this->_defaultDelimiter = first_highest.first;
            _hasDefaultDelimiter = true;
          } else {
            // ask the user waht delimiter ti use
            std::cout << "No suitable delimiter found! Please, enter the delimiter now!" << std::endl;
            std::cin >> this->_defaultDelimiter;
            _hasDefaultDelimiter = true;
          }
        }
        
        
        // second, remove any endline or separator character at the end of the line
        if (line.find_last_of('\n') == line.length())
          line.pop_back();
        while (line.back() == this->_defaultDelimiter) {
          line.pop_back();
        }
        
        
        // Now split the line and store it in the list
        fs::CsvFormat<T> tmp_csv;
        
        found = line.find(this->_defaultDelimiter);
        
        if (found == std::string::npos) {
          throw fs::Exception("No delimiter found");
        }
        
        
        while (found != std::string::npos) {
          // as it might be also possible to have non string input for .csv, a
          // conversion is necessary.
          tmp_csv.addToAline(fs::cast_string<T>(line.substr(0, found)));
          line = line.substr(found+1);
          found = line.find(this->_defaultDelimiter);
        }
        
        
        // considere also the last element
        if (line.empty() == false) {
          tmp_csv.addToAline(fs::cast_string<T>(line));
        }
        
        data.push_back(tmp_csv);
      }
      
      datafile.close();
      std::cout << "Finished reading file: " << *this->_file << std::endl;
    } else {
      throw fs::Exception("Unable to open file: " + *this->_file);
    }

  } catch (fs::Exception &e) {
    std::cout << e.message() << std::endl;
    exit(1);
  }
}



// instantiate those types which can be used
template class fs::CsvReader<short>;
template class fs::CsvReader<unsigned short>;
template class fs::CsvReader<int>;
template class fs::CsvReader<unsigned int>;
template class fs::CsvReader<long>;
template class fs::CsvReader<unsigned long>;
template class fs::CsvReader<float>;
template class fs::CsvReader<double>;

template class fs::CsvReader<std::string>;








