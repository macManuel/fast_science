//
//  bedgraphFormat.h
//  fast_science
//
//
//  Created by Manuel on 20.06.15.
//
//

#ifndef file_formats_bedgraphFormat_h
#define file_formats_bedgraphFormat_h

#include <string>

#include "format.h"

namespace fs {
  
  /**
   *  This class describes an object to store the content of a bed format.
   *  For more information about the format see:
   *  https://genome.ucsc.edu/FAQ/FAQformat.html#format3
   */
  class BedgraphFormat : public Format {
    
  protected:
    
    /**
     *  The name of the chromosome. This value must be set.
     */
    std::string* _chrom;
    
    /**
     *  The starting position inside the chromosome. This value must be set.
     */
    unsigned int _chromStart;
    
    /**
     *  The end position inside the chromosome. This value must be set.
     */
    unsigned int _chromEnd;
    
    /**
     *  A score. This value must be set.
     */
    double _score;
    
    
    
    public:

    /**
     *  A standard constructor.
     */
    BedgraphFormat();
    
    /**
     *  An initializer constructor.
     */
    BedgraphFormat(std::string const & chrom, unsigned int chromStart, unsigned int chromEnd, double score);
    
    /**
     *  A copy constructor.
     */
    BedgraphFormat(fs::BedgraphFormat const & original);
    
    /**
     *  Overloading the = operator.
     *
     *  @param original A const reference to a BedgraphFormat object.
     *
     *  @return A reference to a BedgraphFormat object
     */
    BedgraphFormat& operator= (fs::BedgraphFormat const & original);
    
    /**
     *  The destructor.
     */
    virtual ~BedgraphFormat();
    
    
    /**
     *  Get the chromosme name.
     *
     *  @return A string pointer.
     */
    std::string const & chrom() const;
    
    /**
     *  Get the start position inside the chromosome.
     *
     *  @return A unsigned int pointer.
     */
    unsigned int chromStart() const;
    
    /**
     *  Get the end position inside the chromosoem.
     *
     *  @return A unsigned int pointer.
     */
    unsigned int chromEnd() const;
    
    /**
     *  Get the score.
     *
     *  @return A double pointer.
     */
    double score() const;
    
    
    /**
     *  Set the chromsomome.
     *
     *  @param chrom A string nameing the chromosome.
     */
    void setChrom(std::string const & chrom);

    /**
     *  Set the start posiiton inside the chromosome.
     *
     *  @param chromStart A unsigned int of the start.
     */
    void setChromStart(unsigned int chromStart);
    
    /**
     *  Set the end position inside the chromosome.
     *
     *  @param stop A unsigned int of the end.
     */
    void setChromEnd(unsigned int chromEnd);
    
    /**
     *  Set the score.
     *
     *  @param score A double score.
     */
    void setScore(double score);
    
    };
  
  
  bool operator< (BedgraphFormat const & lhs, BedgraphFormat const & rhs);
  bool operator<= (BedgraphFormat const & lhs, BedgraphFormat const & rhs);
  bool operator> (BedgraphFormat const & lhs, BedgraphFormat const & rhs);
  bool operator>= (BedgraphFormat const & lhs, BedgraphFormat const & rhs);
  bool operator== (BedgraphFormat const & lhs, BedgraphFormat const & rhs);
  bool operator!= (BedgraphFormat const & lhs, BedgraphFormat const & rhs);
}

#endif
