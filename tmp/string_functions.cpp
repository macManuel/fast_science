//
//  string_functions.h
//  fast_science
//
//
//  Created by Manuel on 20.06.15.
//
//

#include "string_functions.h"

bool fs::string_contains_string (std::string const & str1, std::string const &  str2) {

  if (str1.find(str2) != std::string::npos) {
    return true;
  } else {
    return false;
  }
  return true;
}



void capitalize_string (std::string & str) {
  std::transform(str.begin(), str.end(), str.begin(), toupper);
}



void lowercase_string (std::string & str) {
    std::transform(str.begin(), str.end(), str.begin(), tolower);
}



template <typename T>
T fs::string_to_number (std::string const & str) {
  std::istringstream convert(str);
  T number;
  convert >> number;
  return number;
}
template short fs::string_to_number<short> (std::string const & str);
template unsigned short fs::string_to_number<unsigned short> (std::string const & str);
template int fs::string_to_number<int> (std::string const & str);
template unsigned int fs::string_to_number<unsigned int> (std::string const & str);
template long fs::string_to_number<long> (std::string const & str);
template unsigned long fs::string_to_number<unsigned long> (std::string const & str);
template float fs::string_to_number<float> (std::string const & str);
template double fs::string_to_number<double> (std::string const & str);



template <typename T>
T fs::cast_string (std::string const & str) {
  std::istringstream convert(str);
  T cast;
  convert >> cast;
  return cast;
}
template short fs::cast_string<short> (std::string const & str);
template unsigned short fs::cast_string<unsigned short> (std::string const & str);
template int fs::cast_string<int> (std::string const & str);
template unsigned int fs::cast_string<unsigned int> (std::string const & str);
template long fs::cast_string<long> (std::string const & str);
template unsigned long fs::cast_string<unsigned long> (std::string const & str);
template float fs::cast_string<float> (std::string const & str);
template double fs::cast_string<double> (std::string const & str);
template std::string fs::cast_string<std::string> (std::string const & str);



template <typename T>
std::string fs::number_to_string (T number) {
  std::ostringstream convert;
  convert << number;
  return convert.str();
}
template std::string fs::number_to_string<short> (short number);
template std::string fs::number_to_string<unsigned short> (unsigned short number);
template std::string fs::number_to_string<int> (int number);
template std::string fs::number_to_string<unsigned int> (unsigned int number);
template std::string fs::number_to_string<long> (long number);
template std::string fs::number_to_string<unsigned long> (unsigned long number);
template std::string fs::number_to_string<float> (float number);
template std::string fs::number_to_string<double> (double number);
