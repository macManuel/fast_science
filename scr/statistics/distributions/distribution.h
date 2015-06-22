//
//  distribution.h
//  fast_science
//  
//
//  Created by Manuel on 20.06.15.
//
//

#ifndef statistics_distribution_h
#define statistics_distribution_h

#include <vector>
#include <algorithm>

namespace fs {
  
  /**
   *  This class is for a distribution of concrete values.
   */
  class Distribution {
    
  protected:
    /**
     *  A list which stores all elements belonging to the distribution object.
     */
    std::vector<double>* _elements;
    
    
    
  public:
  
    /**
     *  The standard constructor
     */
    Distribution();
    
    /**
     *  The constructor directly filling the element list.
     */
    Distribution(std::vector<double> const & element);
    
    /**
     *  The destructor.
     */
    virtual ~Distribution();
    
    
    /**
     *  Add one Element to the distribution.
     *
     *  @param element The element to add.
     */
    void addElement(double element);
    
    
    
    /**
     *  Method to calculate the value of the p quantile.
     *
     *  @param p A double between 0 and 1.0
     *
     *  @return The last element which is part of the ith quantile.
     */
    double quantile(double p);
    
    
  };
}


#endif
