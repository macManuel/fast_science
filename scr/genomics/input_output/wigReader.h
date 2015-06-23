//
//  wigReader.h
//  fast_science
//
//
//  Created by Manuel on 20.06.15.
//
//

#ifndef input_output_wigReader_h
#define input_output_wigReader_h

#include "reader.h"
#include "bedgraphFormat.h"
#include "string_functions.h"


namespace fs {
  
  /**
   *  Class for reading content from a .wig file.
   */
  class WigReader : public fs::Reader<fs::BedgraphFormat> {
    
  protected:
    
    
    
  private:
    /**
     *  An initializer function used to to some tasks necessary for all
     *  constructors.
     */
    void WigInit();
    
    
  public:
    /**
     *  The constructor for a reader object.
     *
     *  @param file String with the fielname.
     *  @param path String with the path to the file.
     *
     */
    WigReader(std::string const & file, std::string const & path);
    
    /**
     *  A constructor using a composed string of path and filename.
     *
     *  @param fileWithPath A composed string.
     */
    WigReader(std::string const & fileWithPath);
    
    /**
     *  The destructor.
     *
     */
    virtual ~WigReader();
    
    
    /**
     *  The method to read the content from a file.
     */
    virtual void readFromFile(std::list<fs::BedgraphFormat> & data);
  };
}


#endif
