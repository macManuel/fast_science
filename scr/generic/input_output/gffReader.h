//
//  gffReader.h
//  fast_science
//  
//
//  Created by Manuel on 20.06.15.
//
//

#ifndef input_output_gffReader_h
#define input_output_gffReader_h

#include "reader.h"
#include "gffFormat.h"
#include "string_functions.h"

#include <iostream>

namespace fs {
  
  /**
   *  Class for reading content from a .gff file.
   */
  class GffReader : public fs::Reader<fs::GffFormat> {
    
  protected:
    
    /**
     *  A number to indicate the version of the gff file. Can be
     *  either 1, 2 or 3.
     */
    unsigned short _version;
    
    /**
     *  Another delimiter for attributes.
     */
    char _attributeDelimiter;
    
    /**
     *  The dilimiter between key and value.
     */
    char _keyValueDelimiter;
    
    
    
  private:
    /**
     *  An initializer function used to to some tasks necessary for all
     *  constructors.
     */
    void GffInit();
    
  public:
    /**
     *  The constructor for a reader object.
     *
     *  @param file String with the fielname.
     *  @param path String with the path to the file.
     *
     */
    GffReader(std::string const file, std::string const path);
    
    /**
     *  A constructor using a composed string of path and filename.
     *
     *  @param fileWithPath A composed string.
     */
    GffReader(std::string const & fileWithPath);
    
    /**
     *  The destructor.
     *
     */
    virtual ~GffReader();
    
    
    /**
     *  The method to read the content from a file.
     */
    virtual void readFromFile(std::list<fs::GffFormat> & data);
  };
}


#endif
