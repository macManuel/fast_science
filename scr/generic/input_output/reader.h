//
//  reader.h
//  fast_science
//  
//
//  Created by Manuel on 12.06.15.
//
//

#ifndef input_output_reader_h
#define input_output_reader_h

#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <string>

#include "exception.h"
#include "csvFormat.h"
#include "gffFormat.h"
#include "bedgraphFormat.h"


namespace fs {
  
  /**
   *  This is a virtual template base class for a Reader object. A Reader object
   *  is designed to read content from a file. The content is then stored in a 
   *  list which is given as a reference from external to use it throughout the
   *  whole programm.
   */
  template  <class T>
  class Reader {
    
  private:
    
    /**
     *  Prevent accidential copying
     */
    Reader(Reader const & original);
    Reader& operator= (Reader const & original);
    
    
    
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
     *  A vector of file name suffixes. If set, no other suffixes are allowed.
     */
    std::vector<std::string>* _allowedSuffixes;
    
    /**
     *  A vector with characters used to ignore comment lines.
     *  (supports "#", "//", "/ *" ,"%")
     */
    std::vector<std::string>* _comment;
    
    /**
     *  A character which determines a delimiter as used in most files to
     *  seperate the content. Can also be empty if the file does not use it.
     */
    char _defaultDelimiter;
    
    
    
  public:
    /**
     *  The constructor for a reader object.
     *
     *  @param file String with the fielname.
     *  @param path String with the path to the file.
     *
     */
    Reader(std::string const & file, std::string const & path);
    
    /**
     *  A constructor using a composed string of path and filename.
     *
     *  @param fileWithPath A composed string.
     */
    Reader(std::string const & fileWithPath);
    
    /**
     *  The destructor.
     */
    virtual ~Reader();
    
    
    /**
     *  The method to read the content from a file.
     *
     *  @param  A reference to a list in which the read elements are stored.
     */
    virtual void readFromFile(std::list<T> & data) = 0;
  };
}
#endif
