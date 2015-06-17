//
//  string_functions.h
//  fast_science
//
//
//  Created by Manuel on 20.06.15.
//
//

#ifndef strings_string_functions_h
#define strings_string_functions_h

#include <string>
#include <algorithm>
#include <cctype>
#include <sstream>

namespace fs {
  /**
   *  This function test if one string is a substring of another string.
   *
   *  @param str1 The string which might contain str2.
   *  @param str2 The string to be tested if it is part of str1.
   *
   *  @return true if str2 is part of str1.
   */
  bool string_contains_string (std::string const & str1, std::string const & str2);
  
  /**
   *  Capitalzes all letters of a given string.
   *
   *  @param str The string to capitalize.
   */
  void capitalize_string (std::string & str);
  
  /**
   *  Lowercases all letters of a given string.
   *
   *  @param str The string to lowercase.
   */
  void lowercase_string (std::string & str);
  
  /**
   *  Converts a given string to a primitive number data type.
   *
   *  @param str The string to convert.
   *
   *  @return The converted number.
   */
  template <typename T>
  T string_to_number (std::string const & str);
  
  /**
   *  Converts a given string to a given data type.
   *
   *  @param str The string to convert.
   *
   *  @return The converted data type.
   */
  template <typename T>
  T cast_string (std::string const & str);
  
  /**
   *  Converts a primitive number data type to a string value.
   *
   *  @param number The number to convert.
   *
   *  @return The converted string.
   */
  template <typename T>
  std::string number_to_string (T number);
  
}

#endif
