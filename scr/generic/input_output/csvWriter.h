//
//  csvWriter.h
//  fast_science
//
//
//  Created by Manuel on 12.06.15.
//
//

#ifndef input_output_csvWriter_h
#define input_output_csvWriter_h

#include <string>

#include "writer.h"
#include "csvFormat.h"


namespace fs {
  
  /**
   * This class is designed to write content from a CsvFormat list into a file.
   */
  template  <typename T>
  class CsvWriter : public Writer<fs::CsvFormat<T>> {
    
  protected:
    
    
  public:
    
    /**
     *  A constructor for a Writer object with path and filename separated. This
     *  constructor offers also the opertunity to specify the delimiter.
     *
     *  @param file String with the fielname. May include the suffix. If no
     *              suffix is given, ".csv" is used.
     *  @param path String with the path to the file.
     *  @param delimiter Character determin the delimiter to use.
     *
     */
    CsvWriter(std::string const & file, std::string const & path, char delimiter = ';');
    
    /**
     *  A constructor using a composed string of path and filename. The filename
     *  may include the suffix. If no suffix is given, ".csv" is used. This 
     *  constructor offers also the opertunity to specify the delimiter.
     *
     *  @param fileWithPath A composed string of path and filename.
     */
    CsvWriter(std::string const & fileWithPath, char delimiter = ';');
    
    /**
     *  The destructor.
     */
    virtual ~CsvWriter();
    
    
    /**
     *  The method to read the content from a file.
     *
     *  @param  A reference to a list in which the read elements are stored.
     */
    virtual void writeIntoFile(std::list<fs::CsvFormat<T>> const & data);
  };
}
#endif
