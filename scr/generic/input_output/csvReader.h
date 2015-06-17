//
//  csvReader.h
//  fast_science
//
//
//  Created by Manuel on 20.06.15.
//
//

#ifndef input_output_csvReader_h
#define input_output_csvReader_h

#include <istream>
#include <map>

#include "reader.h"
#include "csvFormat.h"
#include "string_functions.h"

namespace fs {
  /**
   *  This is a virtual template base class for a reader object. A reader object
   *  is designed to read content from a file. The content is then internally
   *  stored in a list which can be used as long as the reader object exists.
   */
  template  <typename T>
  class CsvReader : public fs::Reader<fs::CsvFormat<T>> {
    
  protected:
    
    /**
     *  An aray of all delimiters which are teseted if no default delimiter is 
     *  given.(supports '\t', ';', '\s', ',', ':', '.')
     */
    std::map<char, unsigned int>* _delimiters;
    
    /**
     *  A boolean indicating if a delimiter was set by the user.
     */
    bool _hasDefaultDelimiter;
    
    
  private:
    /**
     *  An initializer function used to to some tasks necessary for all
     *  constructors.
     */
    void CsvInit();
    
    
    
  public:
    
    /**
     *  A constructor for a reader object.
     *
     *  @param file String with the fielname.
     *  @param path String with the path to the file.
     *
     */
    CsvReader(std::string const & file, std::string const & path);
    
    /**
     *  A constructor for a reader object.
     *
     *  @param file String with the fielname.
     *  @param path String with the path to the file.
     *  @param delimiter A delimiter which must be used.
     *
     */
    CsvReader(std::string const & file, std::string const & path, char delimiter);
    
    /**
     *  A constructor using a composed string of path and filename.
     *
     *  @param fileWithPath A composed string.
     */
    CsvReader(std::string const & fileWithPath);
    
    /**
     *  A constructor using a composed string of path and filename.
     *
     *  @param fileWithPath A composed string.
     *  @param delimiter A delimiter which must be used.
     */
    CsvReader(std::string const & fileWithPath, char delimiter);
    
    /**
     *  The destructor.
     */
    virtual ~CsvReader();
    
    
    /**
     *  The method to read the content from a file.
     *
     *  @param  A reference to a list in which the read elements are stored.
     */
    virtual void readFromFile(std::list<fs::CsvFormat<T>> & data);
  };
}
#endif
