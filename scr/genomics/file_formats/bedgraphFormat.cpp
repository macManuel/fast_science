//
//  bedgraphFormat.cpp
//  fast_science
//
//
//  Created by Manuel on 20.06.15.
//
//

#include "BedgraphFormat.h"

fs::BedgraphFormat::BedgraphFormat() {
  
  _chrom = new std::string;
}


fs::BedgraphFormat::BedgraphFormat(std::string const & chrom, unsigned int chromStart, unsigned int chromEnd, double score){
  
  _chrom = new std::string(chrom);
  
  _chromStart = chromStart;
  _chromEnd = chromEnd;
  _score = score;
  
}


fs::BedgraphFormat::BedgraphFormat(const BedgraphFormat& original) {
  
  _chrom = new std::string(original.chrom());
  
  _chromStart = original.chromStart();
  _chromEnd = original.chromEnd();
  _score = original.score();
}


fs::BedgraphFormat& fs::BedgraphFormat::operator= (BedgraphFormat const& original) {
  
  if (&original != this) {
    _chrom = new std::string(original.chrom());
      
    _chromStart = original.chromStart();
    _chromEnd = original.chromEnd();
    _score = original.score();
  }
  return *this;
}


fs::BedgraphFormat::~BedgraphFormat() {
 
  delete _chrom;
  _chrom = nullptr;
}


std::string const & fs::BedgraphFormat::chrom() const {
  return *_chrom;
}

unsigned int fs::BedgraphFormat::chromStart() const {
  return _chromStart;
}

unsigned int fs::BedgraphFormat::chromEnd() const {
  return _chromEnd;
}

double fs::BedgraphFormat::score() const {
  return _score;
}



void fs::BedgraphFormat::setChrom(std::string const & chrom) {
  
  *_chrom = chrom;
}


void fs::BedgraphFormat::setChromStart(unsigned int chromStart) {

  _chromStart = chromStart;
}
  

void fs::BedgraphFormat::setChromEnd(unsigned int chromEnd) {

  _chromEnd = chromEnd;
}


void fs::BedgraphFormat::setScore(double score) {

  _score = score;
}



bool fs::operator< (const BedgraphFormat& lhs, const fs::BedgraphFormat& rhs) {
    if (lhs.chrom() < rhs.chrom()) {
        return true;
    } else if (lhs.chrom() == rhs.chrom() && lhs.chromStart() < rhs.chromStart()) {
        return true;
    } else if (lhs.chrom() == rhs.chrom() && lhs.chromStart() == rhs.chromStart() && lhs.chromEnd() < rhs.chromEnd()) {
        return true;
    }
    return false;
}


bool fs::operator> (const fs::BedgraphFormat& lhs, const fs::BedgraphFormat& rhs) {
    if (lhs.chrom() >rhs.chrom()) {
        return true;
    } else if (lhs.chrom() == rhs.chrom() && lhs.chromStart() > rhs.chromStart()) {
        return true;
    } else if (lhs.chrom() == rhs.chrom() && lhs.chromStart() == rhs.chromStart() && lhs.chromEnd() > rhs.chromEnd()) {
        return true;
    }
    return false;
}


bool fs::operator<= (const fs::BedgraphFormat& lhs, const fs::BedgraphFormat& rhs) {
    return !(lhs > rhs);
}


bool fs::operator>= (const fs::BedgraphFormat& lhs, const fs::BedgraphFormat& rhs) {
    return !(lhs < rhs);
}


bool fs::operator== (const fs::BedgraphFormat& lhs, const fs::BedgraphFormat& rhs) {
    if (lhs.chrom() == rhs.chrom() && lhs.chromStart() == rhs.chromStart() && lhs.chromEnd() == rhs.chromEnd()) {
        return true;
    }
    return false;
}


bool fs::operator!= (const fs::BedgraphFormat& lhs, const fs::BedgraphFormat& rhs) {
    return !(lhs == rhs);
}