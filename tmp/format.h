//
//  format.h
//  fast_science
//
//
//  Created by Manuel on 20.06.15.
//
//

#ifndef file_formats_format_h
#define file_formats_format_h

# include <string>

namespace fs {
  /**
   *  This is a base class for any file format.
   *  TODO At the moment there is no real function but maybe it is still good to
   *       have this base class for future expandations.
   */
  class Format {
    
  public:
    
    /**
     *  A standart constructor
     */
    Format();
    
    /**
     *  A copy constructor
     */
    Format(Format const & original);
    
    /**
     *  The = operator.
     */
    Format& operator= (Format const & original);
    
    /**
     *  The destructor.
     */
    virtual ~Format();
  };
}


#endif
