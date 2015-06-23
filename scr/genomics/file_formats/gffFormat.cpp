//
//  gffFormat.cpp
//  fast_science
//
//
//  Created by Manuel on 20.06.15.
//
//

#include "gffFormat.h"

fs::GffFormat::GffFormat() {
  
  _seqname = new std::string;
  _source = new std::string;
  _feature = new std::string;
  
  _hasScore = false;
  _hasStrand = false;
  _hasFrame = false;
  
  _attribute_string = new std::string;
  _hasAttribute_string = false;
  
  _attribute_map = new std::map<std::string, std::string>;
  _hasAttribute_map = false;
  
}


fs::GffFormat::GffFormat(std::string const & seqname, std::string const & source, std::string const & feature, unsigned int start, unsigned int end, double score, char strand, unsigned short frame, std::string const & attribute_string) {
 
  _seqname = new std::string(seqname);
  _source = new std::string(source);
  _feature = new std::string(feature);
  
  _start = start;
  _end = end;
  
  _score = score;
  _hasScore = true;
  _strand = strand;
  _hasStrand = true;
  _frame = frame;
  _hasFrame = true;
  
  _attribute_string = new std::string(attribute_string);
  _hasAttribute_string = true;
  _attribute_map = new std::map<std::string, std::string>;
  _hasAttribute_map = false;
}


fs::GffFormat::GffFormat(std::string const & seqname, std::string const & source, std::string const & feature, unsigned int start, unsigned int end, double score, char strand, unsigned short frame, std::map<std::string, std::string> const & attribute_map) {
  
  
  _seqname = new std::string(seqname);
  _source = new std::string(source);
  _feature = new std::string(feature);
  
  _start = start;
  _end = end;
  
  _score = score;
  _hasScore = true;
  _strand = strand;
  _hasStrand = true;
  _frame = frame;
  _hasFrame = true;
  
  _attribute_string = new std::string;
  _hasAttribute_string = false;
  _attribute_map = new std::map<std::string, std::string>(attribute_map);
  _hasAttribute_map = true;
  
}


fs::GffFormat::GffFormat(fs::GffFormat const & original) {
  
  _seqname = new std::string(original.seqname());
  _source = new std::string(original.source());
	_feature = new std::string(original.feature());
  _start = original.start();
  _end = original.end();

  _score = original.score();
  _hasScore = original.hasScore();
  _strand = original.strand();
  _hasStrand = original.hasStrand();
  _frame = original.frame();
  _hasFrame = original.hasFrame();
 
  _attribute_string = new std::string(original.attribute_string());
  _hasAttribute_string = original.hasAttribute_string();
  _attribute_map = new std::map<std::string, std::string>(original.attribute_map());
  _hasAttribute_map = original.hasAttribute_map();
}


fs::GffFormat&  fs::GffFormat::operator= (fs::GffFormat const & original) {
  
  if(&original != this){
    
    _seqname = new std::string(original.seqname());
    _source = new std::string(original.source());
    _feature = new std::string(original.feature());
    _start = original.start();
    _end = original.end();
    
    _score = original.score();
    _hasScore = original.hasScore();
    _strand = original.strand();
    _hasStrand = original.hasStrand();
    _frame = original.frame();
    _hasFrame = original.hasFrame();
    
    _attribute_string = new std::string(original.attribute_string());
    _hasAttribute_string = original.hasAttribute_string();
    _attribute_map = new std::map<std::string, std::string>(original.attribute_map());
    _hasAttribute_map = original.hasAttribute_map();
  }
  return *this;
}


fs::GffFormat::~GffFormat() {
  
  delete _seqname;
  _seqname = nullptr;
  
  delete _source;
  _source = nullptr;
  
  delete _feature;
  _feature = nullptr;
  
  delete _attribute_string;
  _attribute_string = nullptr;
  
  delete _attribute_map;
  _attribute_map = nullptr;
}



std::string const & fs::GffFormat::seqname() const {
  return *_seqname;
}


std::string const & fs::GffFormat::source() const {
  return *_source;
}


std::string const & fs::GffFormat::feature() const {
  return *_feature;
}


unsigned int fs::GffFormat::start() const {
  return _start;
}


unsigned int fs::GffFormat::end() const {
  return _end;
}


double fs::GffFormat::score() const {
  return  _score;
}

bool fs::GffFormat::hasScore() const {
  return _hasScore;
}

char fs::GffFormat::strand() const {
  return _strand;
}

bool fs::GffFormat::hasStrand() const {
  return _hasStrand;
}

unsigned short fs::GffFormat::frame() const {
  return _frame;
}

bool fs::GffFormat::hasFrame() const {
  return _hasFrame;
}


std::string const & fs::GffFormat::attribute_string() const {
  return *_attribute_string;
}

bool fs::GffFormat::hasAttribute_string() const {
  return _hasAttribute_string;
}

std::map<std::string,std::string> const & fs::GffFormat::attribute_map() const {
  return *_attribute_map;
}

bool fs::GffFormat::hasAttribute_map() const {
  return _hasAttribute_map;
}


void fs::GffFormat::setSeqname(std::string const & seqname) {

  *_seqname = seqname;
}

void fs::GffFormat::setSource(std::string const & source) {
  
  *_source = source;
}

void fs::GffFormat::setFeature(std::string const & feature) {

  *_feature = feature;
}

void fs::GffFormat::setStart(unsigned int start) {

  _start = start;
}

void fs::GffFormat::setEnd(unsigned int end) {

  _end = end;
}

void fs::GffFormat::setScore(double score) {

  _score = score;
  _hasScore = true;
}

void fs::GffFormat::setScore() {
  
  _hasScore = false;
}

void fs::GffFormat::setStrand(char strand) {
  
  _strand = strand;
  _hasStrand = true;
}

void fs::GffFormat::setStrand() {
  
  _hasStrand = false;
}

void fs::GffFormat::setFrame(unsigned short frame) {

  _frame = frame;
  _hasFrame = true;
}

void fs::GffFormat::setFrame() {
  
  _hasFrame = false;
}

void fs::GffFormat::setAttribute_string(std::string const & attribute_string) {
  
	*_attribute_string = attribute_string;
  _hasAttribute_string = true;
  
  // clear the attribute map as only one of the two can be set.
  _attribute_map->clear();
  _hasAttribute_map = false;
}

void fs::GffFormat::setAttribute_string() {
  
  _hasAttribute_string = false;
  _attribute_string->clear();
}


void fs::GffFormat::setAttribute_map(std::map<std::string,std::string> const & attribute_map) {

  *_attribute_map = attribute_map;
  _hasAttribute_map = true;
  
  // clear the attribute string as only one of the two can be set.
  _attribute_string->clear();
  _hasAttribute_string = false;
}

void fs::GffFormat::setAttribute_map() {
  
  _hasAttribute_map = false;
  _attribute_map->clear();
}


void fs::GffFormat::addAttribute(std::string const & key, std::string const &value) {
 
	_attribute_map->insert(std::pair<std::string, std::string>(key,value));
  _hasAttribute_map = true;
  
  // clear the attribute string as only one of the two can be set.
  _attribute_string->clear();
  _hasAttribute_string = false;
}



bool fs::operator < (fs::GffFormat const & lhs, fs::GffFormat const & rhs) {
    if (lhs.seqname() < rhs.seqname()) {
        return true;
    } else if (lhs.seqname() == rhs.seqname() && lhs.start() < rhs.start()) {
        return true;
    } else if (lhs.seqname() == rhs.seqname() && lhs.start() == rhs.start() && lhs.end() < rhs.end()) {
        return true;
    } else {
        return false;
    }
}


bool fs::operator > (fs::GffFormat const & lhs, fs::GffFormat const & rhs) {
    if (lhs.seqname() > rhs.seqname()) {
        return true;
    } else if (lhs.seqname() == rhs.seqname() && lhs.start() > rhs.start()) {
        return true;
    } else if (lhs.seqname() == rhs.seqname() && lhs.start() == rhs.start() && lhs.end() > rhs.end()) {
        return true;
    } else {
        return false;
    }
}


bool fs::operator <= (fs::GffFormat const & lhs, fs::GffFormat const & rhs) {
    if (lhs.seqname() <= rhs.seqname()) {
        return true;
    } else if (lhs.seqname() == rhs.seqname() && lhs.start() <= rhs.start()) {
        return true;
    } else if (lhs.seqname() == rhs.seqname() && lhs.start() == rhs.start() && lhs.end() <= rhs.end()) {
        return true;
    } else {
        return false;
    }
}


bool fs::operator >= (fs::GffFormat const & lhs, fs::GffFormat const & rhs) {
    if (lhs.seqname() >= rhs.seqname()) {
        return true;
    } else if (lhs.seqname() == rhs.seqname() && lhs.start() >= rhs.start()) {
        return true;
    } else if (lhs.seqname() == rhs.seqname() && lhs.start() == rhs.start() && lhs.end() >= rhs.end()) {
        return true;
    } else {
        return false;
    }
}


bool fs::operator == (fs::GffFormat const & lhs, fs::GffFormat const & rhs) {
    if (lhs.seqname() == rhs.seqname() && lhs.start() == rhs.start() && lhs.end() == rhs.start()) {
        return true;
    }
    return false;
}


bool fs::operator != (fs::GffFormat const & lhs, fs::GffFormat const & rhs) {
    if (lhs.seqname() != rhs.seqname() || lhs.start() != rhs.start() || lhs.end() != rhs.start()) {
        return true;
    }
    return false;
}
