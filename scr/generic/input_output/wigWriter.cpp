//
//  WigWriter.h
//  fast_science
//
//
//  Created by Manuel on 20.06.15.
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
      
      unsigned int span = data.begin()->chromEnd() - data.begin()->chromStart();
      bool spanIsConstant = true;
      
      auto next = data.begin();
      ++next;
      unsigned int step = next->chromStart() - data.begin()->chromStart();
      bool stepIsFixed = true;
      
      std::string chromosome = data.begin()->chrom();
      
      
      // remember the start end ending for one chromosome.
      auto start_ptr = data.cbegin();
      auto end_ptr = data.cend();
      
      // go through all the data
      while (start_ptr != data.cend()) {
  
 
        // check for each chromosome what steps and which output can be used
        auto tmp = start_ptr;
        
        while (tmp->chrom() == chromosome && tmp != data.end()) {
          // clculate the span of each entry
          unsigned int tmp_span = tmp->chromEnd() - tmp->chromStart();
          unsigned int tmp_step = tmp->chromStart() - next->chromStart();
          
          if (tmp_span != span) {
            spanIsConstant = false;
          }
          
          if (tmp_step != step) {
            stepIsFixed = false;
            spanIsConstant = false;
          }
          
          tmp++;
          next++;
        }
        
        end_ptr = tmp;
        
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
          // Be aware that or wig files the first position is 1  and not 0 as in bedgraph!
          datafile << "start=" << start_ptr->chromStart()+1 << this->_delimiter;
          datafile << "step=" << step << this->_delimiter;
          datafile << "span=" << span << "\n";
        } else {
          
          // for the variable case
          datafile << "variableStep" << this->_delimiter;
          datafile << "chrom=" << chromosome << this->_delimiter;
          datafile << "span=" << span << "\n";
        }
        
        
        // second, the output as far as we can
        
        for (start_ptr; start_ptr != end_ptr; ++start_ptr) {
          
          if (stepIsFixed == true) {
            // for the fixed case
            datafile << start_ptr->score() << "\n";
          } else {
          
            // for the variable case
              datafile << start_ptr->chromStart() + 1 << this->_delimiter << start_ptr->score() << "\n";
          }
        }
        
        
        // before continuing update for the next chromosome
        span = end_ptr->chromEnd() - end_ptr->chromStart();
        spanIsConstant = true;
        
        next++;
        step = next->chromStart() - end_ptr->chromStart();
        stepIsFixed = true;
        
        chromosome = end_ptr->chrom();
        
        // remember the start end ending for one chromosome.
        start_ptr = end_ptr;
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
