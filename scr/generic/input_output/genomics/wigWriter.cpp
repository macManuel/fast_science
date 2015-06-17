//
//  WigWriter.h
//  fast_science
//
//
//  Created by Manuel on 12.06.15.
//
//


#include "WigWriter.h"

fs::WigWriter::WigWriter(std::string const & file, std::string const & path) : Writer<fs::BedgraphFormat>(file, path){
  
  // every .ggf file has the same delimiter.
  this->_delimiter = '\t';
  *this->_suffix = ".bedgraph";
}


fs::WigWriter::WigWriter(std::string const & fileWithPath) : Writer<fs::BedgraphFormat>(fileWithPath) {
  
  // every .ggf file has the same delimiter.
  this->_delimiter = '\t';
  *this->_suffix = ".bedgraph";
}


fs::WigWriter::~WigWriter() {
  
}



void fs::WigWriter::writeIntoFile(std::list<fs::BedgraphFormat> const & data) {
  
  try {
    // open the file
    std::fstream datafile;
    
    datafile.open(*(this->_path) + *(this->_file) + *(this->_suffix), std::fstream::out | std::fstream::binary);
    
    if (datafile.is_open()){
      
      // wirting wig fles is a bit more tricky because we need to know if we can use fixed step or must use variable step
      
      unsigned int span = data.begin()->chromEnd() - data.begin()->chromStart() + 1;
      bool spanIsConstant = true;
      auto begin_pp = data.begin();
      ++begin_pp;
      unsigned int step = begin_pp->chromStart() - data.begin()->chromStart();
      bool stepIsFixed = true;
      std::string chromosome = data.begin()->chrom();
      
      // remember the start end ending for one chromosome.
      auto start_ptr = data.begin();
      auto end_ptr = data.begin();
      
      
      // check for each chromosome what steps and which output can be used
      for (auto it = data.begin(); it != data.end(); ++it) {
        
        
        // make sure that we do not get into trouble at the end of the chromosome or list.
        auto tmp = it;
        ++tmp;
        
        if (tmp->chrom() == chromosome && tmp != data.end()) {
          // clculate the span of each enty
          unsigned int tmp_span = it->chromEnd() - it->chromStart() + 1;
          unsigned int tmp_step = tmp->chromStart() - it->chromStart();
          
          if (tmp_span != span) {
            spanIsConstant = false;
          }
          
          if (tmp_step != step) {
            stepIsFixed = false;
            spanIsConstant = false;
          }
        
        } else {
          end_ptr = tmp;
        }
        
        // after collecting the data for one chromosome start printing
        // if there is no constant span the data are written out with span = 1
        if (spanIsConstant == false) {
          span = 1;
        }
        
        
        // first, the track line
        
        // for the fixed case
        if (stepIsFixed == true) {
          datafile << "fixedStep" << this->_delimiter;
          datafile << "chrom=" << chromosome << this->_delimiter;
          datafile << "start=" << start_ptr->chromStart() << this->_delimiter;
          datafile << "step=" << start_ptr->chromStart() << this->_delimiter;
          datafile << "span=" << start_ptr->chromStart() << "\n";
        } else {
          
          // for the variable case
          datafile << "variableStep" << this->_delimiter;
          datafile << "chrom=" << chromosome << this->_delimiter;
          datafile << "span=" << start_ptr->chromStart() << "\n";
        }
        
        
        // second, the output as far as we can
        
        for (auto jt = start_ptr; jt != end_ptr; ++jt) {
          
          if (stepIsFixed == true) {
            // for the fixed case we must have a constant span per definition
            datafile << jt->score() << "\n";
          } else {
          
            // the variable case with constant span is also easy to handle
            if (spanIsConstant == true) {
              
              datafile << jt->chromStart() << this->_delimiter << jt->score() << "\n";
            } else {
              
              // this case is a bit more tricky
            
              unsigned int start = jt->chromStart();
              
              while (start != jt->chromEnd()) {
                datafile << start << this->_delimiter << jt->score() << "\n";
                start++;
              }
              datafile << start << this->_delimiter << jt->score() << "\n";
            }
          }
        }
        
        
        // before continuing update for the next chromosome
        
        span = tmp->chromEnd() - tmp->chromStart() + 1;
        spanIsConstant = true;
        auto tmp_pp = tmp;
        tmp_pp++;
        step = (tmp_pp)->chromStart() - tmp->chromStart();
        stepIsFixed = true;
        chromosome = tmp->chrom();
        
        // remember the start end ending for one chromosome.
        start_ptr = tmp;
      }
      
      datafile.close();
      std::cout << "Finished writing file: " << *this->_file << std::endl;
    } else {
      throw fs::Exception("Unable to open file: " + *this->_file);
    }
    
  } catch (fs::Exception &e) {
    std::cout << e.message() << std::endl;
    exit(1);
  }
}
