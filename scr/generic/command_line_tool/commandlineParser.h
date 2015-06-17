//
//  commandlineParser.h
//  fast_science
//
//
//  Created by Manuel on 20.06.15.
//

#ifndef clap_commandlineParser_h
#define clap_commandlineParser_h

#include <list>
#include <vector>
#include <map>
#include <ostream>
#include <iostream>

#include "exception.h"
#include "clapArgument.h"
#include "string_functions.h"
#include "print_functions.h"

namespace fs {
  /**
   * This is the actual class which collects all the methods and variables for
   * parsing the command line arguments.
   */
  class CommandlineParser {
    
    
  private:
    
    /**
     *  The name of the programm extracted from argv[0].
     */
    std::string* _program;
    
    /**
     *  A value representing the version of the program.
     */
    std::string* _version;
    
    /**
     *  A small summary about what the program is intended for.
     */
    std::string* _summary;
    
    
    /**
     *  A list which stores pointers to all the arguments of an instance of the
     *  class in the order of addition
     */
    std::list<fs::ClapArgument*>* _argumentList;
    
    /**
     *  A map which stores pointers to all the arguments of an instance of
     *  the class with thier flags as keys for fast access during parsing
     */
    std::map<std::string, fs::ClapArgument*>* _argumentMap;
    
    
    
  public:
    
    /**
     *  The constructor to be used. This gurantees that for all programms a
     *  a version and short summary is set up.
     */
    CommandlineParser(std::string const & version, std::string const & summary);
    
    /**
     *  The destructor.
     */
    ~CommandlineParser();
    
    
    /**
     *  Method to add an argument to the argument list
     *
     *  @param argument A pointer to an argument.
     */
    void addArgument(fs::ClapArgument* argument);
    
    /**
     *  The most important method responsible for parsing the arguments from
     *  the command line.
     */
    void parse(int argc, const char * const * argv);
    
    
  protected:
    
    /**
     *  An internal method to print the long help page.
     */
    void printHelp();
    
    /**
     *  An internal method to print short usage information.
     */
    void printUsage();
    
    /**
     *  An internal method to print the version of the program.
     */
    void printVersion();
    
  };

}

#endif
