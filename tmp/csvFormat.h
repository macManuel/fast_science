//
//  csvFormat.h
//  fast_science
//
//
//  Created by Manuel on 20.06.15.
//
//

#ifndef file_formats_csvFormat_h
#define file_formats_csvFormat_h

#include <list>
#include <string>
#include <iostream>

namespace fs {
  
  /**
   *  This template class is designed to store elements as found in one line of 
   *  a .csv file.
   */
  template <class T>
  class CsvFormat {
    
  protected:
   
    /**
     *  A list of type T to store the elements.
     */
    std::list<T>* _aline;
        
  public:
    
    /**
     *  The standard constructor
     */
    CsvFormat();
    
    /**
     *  A constructor directly adding a list.
     */
    CsvFormat(std::list<T> const & line);
    
    /**
     *  The copy constructor.
     */
    CsvFormat(CsvFormat const & original);

    /**
     *  The = operator.
     */
    CsvFormat& operator= (CsvFormat const & original);
    
    /**
     *  The destructor.
     */
    virtual ~CsvFormat();
        
    
    /**
     *  Get the list arguments for read only purposes.
     *
     *  @return A const reference to the list.
     */
    std::list<T> const & aline() const;
    
    /**
     *  Set a new list.
     *
     *  @param aline The new list.
     */
    void setAline(std::list<T> const & aline);
    
    /**
     *  Add one element to the list.
     *
     *  @param toAdd The element to add.
     */
    void addToAline(T const & toAdd);
    };
}
#endif
