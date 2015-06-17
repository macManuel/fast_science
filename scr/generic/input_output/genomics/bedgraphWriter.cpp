//
//  bedgraphWriter.h
//  fast_science
//
//
//  Created by Manuel on 12.06.15.
//
//


#include "bedgraphWriter.h"

fs::BedgraphWriter::BedgraphWriter(std::string const & file, std::string const & path) : Writer<fs::BedgraphFormat>(file, path){
  
  // every .ggf file has the same delimiter.
  this->_delimiter = '\t';
  *this->_suffix = ".bedgraph";
}


fs::BedgraphWriter::BedgraphWriter(std::string const & fileWithPath) : Writer<fs::BedgraphFormat>(fileWithPath) {
  
  // every .ggf file has the same delimiter.
  this->_delimiter = '\t';
  *this->_suffix = ".bedgraph";
}


fs::BedgraphWriter::~BedgraphWriter() {
  
}



void fs::BedgraphWriter::writeIntoFile(std::list<fs::BedgraphFormat> const & data) {
  
  try {
    // open the file
    std::fstream datafile;
    
    datafile.open(*(this->_path) + *(this->_file) + *(this->_suffix), std::fstream::out | std::fstream::binary);
    
    if (datafile.is_open()){
      
      for (auto it = data.begin(); it != data.end(); ++it) {
        
        // wite out one value after another
        
        // the chromosome
        datafile << it->chrom() << this->_delimiter;
        
        // the start
        datafile << it->chromStart() << this->_delimiter;
        
        // the end
        datafile << it->chromEnd() << this->_delimiter;
        
        // the score
        datafile << it->score();
        
        // and a end line character at the end
        datafile << "\n";
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
