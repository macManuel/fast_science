//
//  gffWriter.h
//  fast_science
//
//
//  Created by Manuel on 12.06.15.
//
//


#ifndef input_output_gffWriter_h
#define input_output_gffWriter_h

#include <string>

#include "writer.h"
#include "gffFormat.h"

namespace fs {
  
  /**
   * This class is designed to write content from a gffFormat list into a file.
   */
  class GffWriter : public fs::Writer<fs::GffFormat> {
    
  protected:
    
    /**
     *  A number determining the version which should be used for output. Can be 
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
    
    
    
    
  public:
    
    /**
     *  A constructor for a Writer object with path and filename separated. This
     *  constructor offers also the opertunity to specify the delimiter.
     *
     *  @param file String with the fielname. May include the suffix. If no
     *              suffix is given, ".csv" is used.
     *  @param path String with the path to the file.
     *  @param version Determin the version of gff to use for the output (1,2,3).
     *
     */
    GffWriter(std::string const & file, std::string const & path, unsigned short version = 3);
    
    /**
     *  A constructor using a composed string of path and filename. The filename
     *  may include the suffix. If no suffix is given, ".csv" is used. This
     *  constructor offers also the opertunity to specify the delimiter.
     *
     *  @param fileWithPath A composed string of path and filename.
     *  @param version Determin the version of gff to use for the output (1,2,3).
     *
     */
    GffWriter(std::string const & fileWithPath, unsigned short version = 3);
    
    /**
     *  The destructor.
     */
    virtual ~GffWriter();
    
    
    /**
     *  The method to read the content from a file.
     *
     *  @param  A reference to a list in which the read elements are stored.
     */
    virtual void writeIntoFile(std::list<fs::GffFormat> const & data);
  };
}
#endif
