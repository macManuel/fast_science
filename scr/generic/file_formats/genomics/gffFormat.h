//
//  gffFormat.h
//  fast_science
//
//
//  Created by Manuel on 20.06.15.
//
//

#ifndef file_formats_gffFormat_h
#define file_formats_gffFormat_h

#include <string>
#include <map>

#include "format.h"

namespace fs {

  /**
   *  An object to store content of a gff file.
   *  The objects support storage of conten for gff/gtf version 1 - 3.
   *  For more information of the file formats see:
   *  http://www.sanger.ac.uk/resources/software/gff/spec.html
   *  http://mblab.wustl.edu/GTF2.html
   *  http://www.sequenceontology.org/gff3.shtml
   */
  class GffFormat : public fs::Format {
    
  protected:
    /**
     *  The name of the sequence. Often used to describe the chromosome.
     */
    std::string* _seqname;
    
    /**
     *  The source of the sequence.
     */
    std::string* _source;
    
    /**
     *  A tag describing the feature of the sequence.
     */
    std::string* _feature;
    
    /**
     *  The start position of the sequence with the first position being 1.
     */
    unsigned int _start;
    
    /**
     *  The end position of the sequence.
     */
    unsigned int _end;
    
    /**
     *  The score for the sequence. Can be empty (.) if not set.
     */
    double _score;
    
    /**
     *  A booelan to control if the gff onject has a score set.
     */
    bool _hasScore;
    
    /**
     *  The strand. Either +, - or if not relevant.
     */
    char _strand;
    
    /**
     *  A booelan to control if the gff onject has a strand set.
     */
    bool _hasStrand;
    
    /**
     *  The reading frame. 0, 1, 2.
     */
    unsigned short _frame;
    
    /**
     *  A booelan to control if the gff onject has a frame set.
     */
    bool _hasFrame;
    
    /**
     *  A single string describtion used for gff version 1.
     */
    std::string* _attribute_string;
    
    /**
     *  A booelan to control if the gff onject has a attribute string set.
     */
    bool _hasAttribute_string;
    
    /**
     *  A key - value description of the sequence.
     */
    std::map<std::string, std::string>* _attribute_map;
  
    /**
     *  A booelan to control if the gff onject has a attribute map set.
     */
    bool _hasAttribute_map;
  
  
  public:
  
    /**
     *  The constructor to create an empty GffFormat object.
     */
    GffFormat();
    
    /**
     *  A constructor for a full gff version 1 object.
     */
    GffFormat(std::string const & seqname, std::string const & source, std::string const & feature, unsigned int start, unsigned int end, double score, char strand, unsigned short frame, std::string const & attribute_string);
    
    /**
     *  A constructor for a full gff version 2 - 3 object.
     */
    GffFormat(std::string const & seqname, std::string const & source, std::string const & feature, unsigned int start, unsigned int end, double score, char strand, unsigned short frame, std::map<std::string, std::string> const & attribute_map);
    
    /**
     *  A copy constructor.
     */
    GffFormat(fs::GffFormat const & original);
    
    /**
     *  Overloading the = operator.
     *
     *  @param gff A const reference to a GffFormat object.
     *
     *  @return A reference to a GffFormat object
     */
    GffFormat& operator= (fs::GffFormat const & original);
    
    /**
     *  The destructor.
     */
    virtual ~GffFormat();
    
    
    /**
     *  Get the seqname.
     *
     *  @return A string pointer.
     */
    std::string const & seqname() const;
    
    /**
     *  Get the source.
     *
     *  @return A string pointer.
     */
    std::string const & source() const;
    
    /**
     *  Get the feature.
     *
     *  @return A string pointer.
     */
    std::string const & feature() const;
    
    /**
     *  Get the start.
     *
     *  @return A unsigned int pointer.
     */
    unsigned int start() const;
    
    /**
     *  Get the end.
     *
     *  @return A unsigned int pointer.
     */
    unsigned int end() const;
    
    /**
     *  Get the score.
     *
     *  @return A doule pointer.
     */
    double score() const;
    
    /**
     *  Get if the score is set.
     *
     *  @return A boolean.
     */
    bool hasScore() const;
    
    /**
     *  Get the strand.
     *
     *  @return A char pointer.
     */
   char strand() const;
    
    /**
     *  Get if the strand is set.
     *
     *  @return A boolean.
     */
    bool hasStrand() const;
    
    /**
     *  Get the frame.
     *
     *  @return a unsigned short pointer.
     */
    unsigned short frame() const;
    
    /**
     *  Get if the frame is set.
     *
     *  @return A boolean.
     */
    bool hasFrame() const;
    
    /**
     *  Get the attribute string.
     *
     *  @return A string pointer.
     */
    std::string const & attribute_string() const;
    
    /**
     *  Get if the attribute string is set.
     *
     *  @return A boolean.
     */
    bool hasAttribute_string() const;
    
    /**
     *  Get the attribute map.
     *
     *  @return A map pointer.
     */
    std::map<std::string,std::string> const & attribute_map() const;
    
    /**
     *  Get if the attribute map is set.
     *
     *  @return A boolean.
     */
    bool hasAttribute_map() const;
    
    /**
     *  Set the seqname.
     *
     *  @param seqname A string describing the sequence's name.
     */
    void setSeqname(std::string const & seqname);
   
    /**
     *  Set the source.
     *
     *  @param source A string describing the source of the sequence.
     */
    void setSource(std::string const & source);
    
    /**
     *  Set the feature.
     *
     *  @param feature A string describing the feature of the sequence.
     */
    void setFeature(std::string const & feature);
    
    /**
     *  Set the sequence start.
     *
     *  @param start A unsigned int of the start value.
     */
    void setStart(unsigned int start);
    
    /**
     *  Set the sequence end value.
     *
     *  @param end A unsigned int of the end value.
     */
    void setEnd(unsigned int end);
    
    /**
     *  Set the score.
     *
     *  @param score A double value for the score.
     */
    void setScore(double score);
    /**
     *  Use this if you want to set no score.
     */
    void setScore();
    
    /**
     *  Set the strand.
     *
     *  @param strand A char for the strand (either +, - or)
     */
    void setStrand(char strand);
    /**
     *  Use this if you want to set no strand.
     */
    void setStrand();
    
    /**
     *  Set the frame.
     *
     *  @param frame A unsigned short for the frame.
     */
    void setFrame(unsigned short frame);
    /**
     *  Use this if you want to set no frame.
     */
    void setFrame();
    
    /**
     *  Set the attribute string.
     *
     *  @param attribute_string A string beeing the attribute.
     */
    void setAttribute_string(std::string const & attribute_string);
    /**
     *  Use this if you want to set no attribute string.
     */
    void setAttribute_string();
    
    /**
     *  Set the attribute map.
     *
     *  @param std::map<std::string,std::string> A attribute map.
     */
    void setAttribute_map(std::map<std::string ,std::string> const & attribute_map);
    /**
     *  Use this if you want to set no attribute map.
     */
    void setAttribute_map();
    
    /**
     *  A method to add one attribute to the attribute map.
     *
     *  @param key   A string with the key.
     *  @param value A string describing the value.
     */
    void addAttribute(std::string const & key, std::string const & value);
    };
    
  /**
   *  The relationship operatoren.
   *
   */
	bool operator< (fs::GffFormat const & lhs, fs::GffFormat const & rhs);
  bool operator<= (fs::GffFormat const & lhs, fs::GffFormat const & rhs);
  bool operator> (fs::GffFormat const & lhs, fs::GffFormat const & rhs);
  bool operator>= (fs::GffFormat const & lhs, fs::GffFormat const & rhs);
  bool operator== (fs::GffFormat const & lhs, fs::GffFormat const & rhs);
  bool operator!= (fs::GffFormat const & lhs, fs::GffFormat const & rhs);
}
#endif
