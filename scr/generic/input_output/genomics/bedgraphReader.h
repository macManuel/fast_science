//
//  bedgraphReader.h
//  fast_science
//
//
//  Created by Manuel on 20.06.15.
//
//

#ifndef input_output_bedgraphReader_h
#define input_output_bedgraphReader_h

#include "reader.h"
#include "bedgraphFormat.h"
#include "string_functions.h"


namespace fs {
  
  /**
   *  Class for reading content from a .bedgraph file.
   */
  class BedgraphReader : public fs::Reader<fs::BedgraphFormat> {
    
  protected:
    
    
    
  private:
    /**
     *  An initializer function used to to some tasks necessary for all
     *  constructors.
     */
    void BedgraphInit();
    
    
  public:
    /**
     *  The constructor for a reader object.
     *
     *  @param file String with the fielname.
     *  @param path String with the path to the file.
     *
     */
    BedgraphReader(std::string const & file, std::string const & path);
    
    /**
     *  A constructor using a composed string of path and filename.
     *
     *  @param fileWithPath A composed string.
     */
    BedgraphReader(std::string const & fileWithPath);
    
    /**
     *  The destructor.
     *
     */
    virtual ~BedgraphReader();
    
    
    /**
     *  The method to read the content from a file.
     */
    virtual void readFromFile(std::list<fs::BedgraphFormat> & data);
  };
}


#endif
