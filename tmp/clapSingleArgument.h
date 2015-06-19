//
//  clapSingleArgument.h
//  fast_science
//
//
//  Created by Manuel on 20.06.15.
//

#ifndef clap_clapSingleArgument_h
#define clap_clapSingleArgument_h

#include <set>
#include <string>

#include "clapArgument.h"
#include "commandlineParser.h"

namespace fs {
  
  template <class T>
  class ClapSingleArgument : public fs::ClapArgument {
    
    
  protected:
    /**
     *  The value of the Argument, which is parsed from the command line.
     */
    T* _value;
    
    /**
     *  A set of constraints which define all the values to be used.
     *  However, it is not necessary to set up this set as there must not be
     *  any constraint.
     */
    std::set<T>* _valueConstraints;
    
    
    
  public:
    
    /**
     *  A constructor for an argument which is not a boolean switch.
     *  This constructor sets no constraints to the values.
     */
    ClapSingleArgument(fs::CommandlineParser & parser, std::string const & flag, std::string const & usageDescription, std::string const & longDescription, bool isRequired = true, bool isSwitch = false);
    
    /**
     *  Constructor setting some constraints to the vlaues.
     *  This constructor sets constraints to the values.
     */
    ClapSingleArgument(fs::CommandlineParser & parser, std::string const & flag, std::set<T>  const & valueConstraints, std::string const & usageDescription, std::string const & longDescription, bool isRequired = true, bool isSwitch = false);
    
    /**
     *  A constructor for an argument which is a boolean switch.
     *  For switch arguments constraints cannot be set.
     *
     */
    ClapSingleArgument(fs::CommandlineParser& parser, char const & flag, std::string const & usageDescription, std::string const & longDescription, bool isRequired = true, bool isSwitch = true);
    
    /**
     *  A destructor for an argument.
     */
    virtual ~ClapSingleArgument();
    
    
    /**
     *  This method returns a const reference to the value for reading purposes.
     *  Be aware that the argument and the parser must be destroyed only after
     *  the argument was used.
     *
     *  @return A const reference of the argument value.
     */
    T const & value() const;
    
    /**
     *  Method to set the value of the argument read from the command line.
     *
     *  @param value The value to be set as a string.
     */
    virtual void setValue(std::string const & valueRead);
    
    
    
  protected:
    /**
     *  This internal method checks wether the value given for the argument can
     *  be set correctly. Otherwise an exception is thrown.
     */
    bool isValid(T const & value) const;
    
  };

}


#endif
