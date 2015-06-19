//
//  print_functions.cpp
//  fast_science
//
//
//  Created by Manuel on 20.06.15.
//
//

#include "print_functions.h"

void fs::space_print(std::ostream& os, std::string const & str, int maxWidth, int indentSpaces, int secondLineOfFSet) {

  int len = static_cast<int>(str.length());
  
  if ( (len + indentSpaces > maxWidth) && maxWidth > 0 )
		{
      int allowedLen = maxWidth - indentSpaces;
      int start = 0;
      while ( start < len )
      {
        // find the substring length
        // int stringLen = std::min<int>( len - start, allowedLen );
        // doing it this way to support a VisualC++ 2005 bug
        using namespace std;
        int stringLen = min<int>( len - start, allowedLen );
        
        // trim the length so it doesn't end in middle of a word
        if ( stringLen == allowedLen )
          while ( stringLen >= 0 &&
                 str[stringLen+start] != ' ' &&
                 str[stringLen+start] != ',' &&
                 str[stringLen+start] != '|' )
            stringLen--;
        
        // ok, the word is longer than the line, so just split
        // wherever the line ends
        if ( stringLen <= 0 )
          stringLen = allowedLen;
        
        // check for newlines
        for ( int i = 0; i < stringLen; i++ )
          if ( str[start+i] == '\n' )
            stringLen = i+1;
        
        // print the indent
        for ( int i = 0; i < indentSpaces; i++ )
          os << " ";
        
        if ( start == 0 )
        {
          // handle second line ofFSets
          indentSpaces += secondLineOfFSet;
          
          // adjust allowed len
          allowedLen -= secondLineOfFSet;
        }
        
        os << str.substr(start,stringLen) << std::endl;
        
        // so we don't start a line with a space
        while ( str[stringLen+start] == ' ' && start < len )
          start++;
        
        start += stringLen;
      }
    }
  else
		{
      for ( int i = 0; i < indentSpaces; i++ )
        os << " ";
      os << str << std::endl;
    }
}