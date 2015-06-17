//
//  exception.h
//  fast_science
//
//
//  Created by Manuel on 20.06.15.
//
//

#ifndef exceptions_exception_h
#define exceptions_exception_h

#include <string>

namespace fs {
  /**
   *  A exception class which can be thrown when an exception occures.
   */
  class Exception {
    
  protected:
    /**
     *  The message string describing the exception.
     */
    std::string* _message;
    
    
    
  public:
    /**
     *  The constructor. It takes a single string as a message.
     */
    Exception(std::string const & message);
    
    /**
     *  The destructor.
     */
    ~Exception();
    
    /**
     *  Returns the exception message for output.
     *
     *  @return A string pointer.
     */
    std::string const & message() const;
    
  };
}

#endif

