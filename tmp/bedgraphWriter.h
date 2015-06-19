//
//  bedgraphWriter.h
//  fast_science
//
//
//  Created by Manuel on 12.06.15.
//
//

#ifndef input_output_bedgraphWriter_h
#define input_output_bedgraphWriter_h

#include <string>

#include "writer.h"
#include "BedgraphFormat.h"

namespace fs {
  
  /**
   * This class is designed to write content from a bedgraphFormat list into a file.
   */
  class BedgraphWriter : public Writer<fs::BedgraphFormat> {
    
  protected:
    
    
  public:
    
    /**
     *  A constructor for a Writer object with path and filename separated.
     *
     *  @param file String with the fielname. The filename may include the 
     *  suffix but if not ".bedgraph" is used.
     *  @param path String with the path to the file.
     *
     */
    BedgraphWriter(std::string const & file, std::string const & path);
    
    /**
     *  A constructor using a composed string of path and filename. The filename
     *  may include the suffix but if not ".bedgraph" is used..
     *
     *  @param fileWithPath A composed string of path and filename.
     */
    BedgraphWriter(std::string const & fileWithPath);
    
    /**
     *  The destructor.
     */
    virtual ~BedgraphWriter();
    
    
    /**
     *  The method to read the content from a file.
     *
     *  @param  A reference to a list in which the read elements are stored.
     */
    virtual void writeIntoFile(std::list<fs::BedgraphFormat> const & data);
  };
}
#endif
