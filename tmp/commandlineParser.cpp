//
//  commandlineParser.cpp
//  fast_science
//
//
//  Created by Manuel on 20.06.15.
//

#include "commandlineParser.h"


fs::CommandlineParser::CommandlineParser(std::string const & version, std::string const & summary) {
  
  _program = new std::string;
  _version = new std::string(version);
  _summary = new std::string(summary);
  _argumentList = new std::list<fs::ClapArgument*>;
  _argumentMap = new std::map<std::string, fs::ClapArgument*>;
}


fs::CommandlineParser::~CommandlineParser() {
  
  delete _program;
  _program = nullptr;
  
  delete _version;
  _version = nullptr;
  
  delete _summary;
  _summary = nullptr;
  
  delete _argumentList;
  _argumentList = nullptr;
  
  delete _argumentMap;
  _argumentMap = nullptr;
}



void fs::CommandlineParser::addArgument(ClapArgument* argument) {
  this->_argumentList->push_back(argument);
  this->_argumentMap->emplace(argument->flag(),argument);
}



void fs::CommandlineParser::parse(int argc, const char * const * argv) {
  
  // The parsing is the most critical step as you never now what the user might
  // have entered. Therefore it might be necessary to throw exceptions and
  // terminate the program.
  
  try {
    // first get all the arguments and copy them into a vector for easy access
    // and modification
    
    std::vector<std::string> arguments;
    for (int i = 0; i < argc; i++) {
      arguments.push_back(argv[i]);
    }
    
    // now extraxt the program name as the first argument
    _program = new std::string;
    *_program = arguments.front();
    arguments.erase(arguments.begin());
    
    
    // see also if the programm name is a path which shuould be cutted
    std::size_t found = _program->find_last_of("/\\");
    if (found != std::string::npos) {
      *_program = _program->substr(found+1);
    }

    // next check if there are any arguments given at all. If not show the help
    // page
    if (arguments.size() == 0) {
      printHelp();
      exit(1);
    }
    
    // next ckeck if the argument is the help argument
    if (arguments.front().compare("--help") == 0) {
      printHelp();
      exit(0);
    }
    
    // or if the user wants the version output
    if (arguments.front().compare("--version") == 0) {
      printVersion();
      exit(0);
    }
      
    // if this is not the case:
    
    // next check if there are really all positional arguments given.
    // This should be done for each required argument independently to be sure
    
    // go through all arguments
    
    for (auto it = _argumentList->cbegin(); it != _argumentList->cend(); ++it) {
      bool found = true;
      // see if it is a positional argument
      if ((*it)->isRequired() == true) {
        found = false;
        
        // see if it is a boolean switch
        if ((*it)->isSwitch() == true) {
          
          // now go through the argument list an stop if the arguments start with
          // an '-'
          for (auto jt = arguments.cbegin(); jt != arguments.cend(); jt++) {
            if (jt->at(0) == '-' && jt->at(1) != '-') {
              
              // test if the argument is part of the read string
              if (fs::string_contains_string(*jt, (*it)->flag()) == true) {
                found = true;
              }
            }
          }
          
          // if it is no boolean swich argument
        } else {
          // go again through the argument list and stop at those argument which
          // start with an '--'
          for (auto jt = arguments.cbegin(); jt != arguments.cend(); jt++) {
            if (jt->at(0) == '-' && jt->at(1) == '-')
              
              // test if the argument is part of the read string
              if (string_contains_string(*jt, (*it)->flag()) == true) {
                found = true;
              }
          }
        }
      }
      if (found == false) {
        throw (fs::Exception ("Argument " + (*it)->flag() + " not found"));
      }
    }
    
    // now parse through all the command line words and set the values accordingly
    
    std::string lastArg;
    int i = 0;
    while (i < arguments.size()) {
      
      std::string current = arguments.at(i);
      // first check if it is an arguemnt
      if (current.front() == '-') {
        
        // if the argument is no boolean flag
        if (current.at(1) == '-') {
          
          // just note that we have to collect the following values for this
          // argument
          current = current.substr(2);
          lastArg = current;
          
        } else {
          
          // set the switch accordingly
          _argumentMap->at(lastArg)->setValue("true");
          // last argument should be empty, as there can no values be set
          lastArg.clear();
        }
      // otherwise it thould be a value to set for the last argument
      } else {
        if (lastArg.empty() == false) {
          
          _argumentMap->at(lastArg)->setValue(current);
        
        } else {
          throw (fs::Exception ("No argument found for"));
        }
      }
      ++i;
    }
  } catch (fs::Exception &e) {
    std::cout << e.message() << std::endl;
    std::cout << std::endl;
    printHelp();
    exit(1);
  }
}


void fs::CommandlineParser::printUsage() {
  
  std::cout << *_summary << std::endl;
  std::cout << std::endl;
  
  std::cout << "Usage: " << *this->_program << " [Options] ";
  
  for (auto it = this->_argumentList->cbegin(); it != this->_argumentList->cend(); ++it) {
    if ((*it)->isRequired() == true && (*it)->isSwitch() == false) {
      std::cout << (*it)->usageDescription() << " ";
    }
  }
  std::cout << std::endl;
}


void fs::CommandlineParser::printHelp() {
  
  // set up a stream for output
  printUsage();
  
  // go through all the arguments and first look for required arguments
  for (auto it = this->_argumentList->cbegin(); it != this->_argumentList->cend(); ++it) {
    
    if ((*it)->isRequired() == true && (*it)->isSwitch() == false) {
      space_print(std::cout, "--" + (*it)->flag(), 75, 3, 3 );
      space_print(std::cout, (*it)->longDescription(), 75, 15, 0);
      std::cout << std::endl;
    }
  }
  
  std::cout << "[Options]" << std::endl;
  std::cout << std::endl;
  
  for (auto it = this->_argumentList->cbegin(); it != this->_argumentList->cend(); ++it) {
    
    if ((*it)->isRequired() == false && (*it)->isSwitch() == false) {
      space_print(std::cout, "--" + (*it)->flag(), 75, 3, 3 );
      space_print(std::cout, (*it)->longDescription(), 75, 15, 0 );
      std::cout << std::endl;
    }
  }
}


void fs::CommandlineParser::printVersion() {
  std::cout << std::endl << *_program << "  version: " << *_version << std::endl << std::endl;
}



