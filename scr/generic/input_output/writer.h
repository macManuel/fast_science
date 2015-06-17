//
//  writer.h
//  fast_science
//
//
//  Created by Manuel on 20.06.15.
//
//

#ifndef input_output_writer_h
#define input_output_writer_h

#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <vector>

#include "exception.h"
#include "csvFormat.h"
#include "gffFormat.h"
#include "bedgraphFormat.h"


namespace fs {
  
  /**
   *  This is a virtual template base class for a Writer object. A Writer object
   *  is designed to write content into a file. The content is then stored in a
   *  list which is given as a const reference from external.
   */
  template  <typename T>
  class Writer {
    
  private:
    // prevent copying
    Writer(Writer const & original);
    Writer& operator= (Writer const & original);
    
    
  protected:
    
    /**
     *  The path where to find the file. Can be empty if the the program
     *  operates on a current path.
     */
    std::string* _path;
    
    /**
     *  The filename to read from.
     */
    std::string* _file;
    
    /**
     *  The suffix of the file.
     */
    std::string* _suffix;
    
    /**
     *  A character which determines a delimiter as used in most files to
     *  seperate the content. Can also be empty if the file does not use it.
     */
    char _delimiter;
    
    
  public:
    
    /**
     *  A constructor for a Writer object with path and filename separated.
     *
     *  @param file String with the fielname. May include the suffix.
     *  @param path String with the path to the file.
     *
     */
    Writer(std::string const & file, std::string const & path);
    
    /**
     *  A constructor using a composed string of path and filename. The filename
     *  may include the suffix.
     *
     *  @param fileWithPath A composed string of path and filename.
     */
    Writer(std::string const & fileWithPath);
    
    /**
     *  The destructor.
     */
    virtual ~Writer();
    
    
    /**
     *  The method to write the content into a file.
     *
     *  @param  A reference to a list in which the elements to write are stored.
     */
    virtual void WriteIntoFile(std::list<T> const & data) = 0;
  };
}

#endif
