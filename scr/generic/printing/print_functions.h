//
//  print_functions.h
//  fast_science
//
//
//  Created by Manuel on 20.06.15.
//
//

#ifndef printing_print_functions_h
#define printing_print_functions_h

#include <iostream>
#include <string>

namespace fs {
  /**
   *  This function inserts line breaks and indents long strings
   *  according the  params input. It will only break lines at spaces,
   *  commas and pipes.
   *
   *  @param os               The stream to be printed to.
   *  @param string           The string to be printed.
   *  @param maxWidth         The maximal width allowed for the output line.
   *  @param indentSpaces     The number of spaces to indent the first line.
   *  @param secondLineOfFSet The number of spaces to indent the second and all
   *                          subsequent lines in addition to indentSpaces.
   */
  void space_print(std::ostream& os, std::string const & str, int maxWidth, int indentSpaces, int secondLineOfFSet);
}

#endif

