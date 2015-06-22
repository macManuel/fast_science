//
//  fileChecker.h
//  fast_science
//  
//
//  Created by Manuel on 20.06.15.
//
//

#ifndef input_output_fileChecker_h
#define input_output_fileChecker_h

#include <string>

#include "string_functions.h"

namespace fs {
  
  /**
   *  This class is to check what is the suffix of a given file.
   */
  class FileChecker {
    
  protected:
    
    /**
     *  Boolean indicating if the file is a .csv file.
     */
    bool _isCsv;
    
    /**
     *  Boolean indicating if the file is a .gff or .gtf file.
     */
    bool _isGff;
    
    /**
     *  Boolean indicating if the file is a .bedgraph file.
     */
    bool _isBedgraph;
    
    /**
     *  Boolean indicating if the file is a .wig file.
     */
    bool _isWig;
    
    
    
    
  private:
    
    /**
     *  Prevent accidential copying
     */
    FileChecker(FileChecker const & original);
    FileChecker& operator= (FileChecker const & original);
    
    
  
  public:
    /**
     *  The constructor for a reader object.
     */
    FileChecker();
    
    
    /**
     *  The destructor.
     */
    virtual ~FileChecker();
    
    
    /**
     *  Get the isCsv value.
     *
     *  @return True if .csv was found.
     */
    bool isCsv() const;
    
    /**
     *  Get the isGff value.
     *
     *  @return True if .gff or .gtf was found.
     */
    bool isGff() const;
    
    /**
     *  Get the isBedgraph value.
     *
     *  @return True if .bedgraph was found.
     */
    bool isBedgraph() const;
    
    /**
     *  Get the isWig value.
     *
     *  @return True if .wig was found.
     */
    bool isWig() const;
    
    
    
    /**
     *  The method to find out which kind of file there is.
     *
     *  @param file The filename which must include the suffix.
     */
    void check(std::string const & file);
  };
}
#endif
