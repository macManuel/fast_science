//
//  clapArgument.h
//  fast_science
//
//
//  Created by Manuel on 20.06.15.
//

#ifndef clap_clapArgument_h
#define clap_clapArgument_h


#include <string>
#include <sstream>


namespace fs {
  /**
   *  This is the interface class for an argument to be parsed from the comand
   *  line. It can not be instantiated as some important functions are totally
   *  virtual.
   */
  
  class ClapArgument {
  
  protected:
  
    /**
     *  A unique flag to name the command line argument. Note that boolean
     *  switch arguments are only allowed to consists of one character while
     *  all other options must be longer.
     */
    std::string* _flag;
    
    /**
     *  This string determined the hyphen which must be present in front of an
     *  argument. For boolean swithches the value is set to "-" and it
     *  sufficient if the first option has the flag. For all other arguments the
     *  value is set to "--" and must be present in any case.
     */
    std::string* _hyphen;
    
    /**
     *  A boolean indicating if the argument is required or not.
     */
    bool _isRequired;
    
    /**
     *  A boolean indicating if the argument is a boolean switch argument or not.
     */
    bool _isSwitch;
    
    /**
     *  A string describing used to build the usage information.
     */
    std::string* _usageDescription;
    
    /**
     *  A string descriping the argument in detail. This is needed to generate
     *  the help message.
     */
    std::string* _longDescription;
    
    
    /**
     *  A boolean which indicates if the value was set, that means if the
     *  was set by the user.
     */
    bool _isSet;
    
    
    
  public:
    
    /**
     *  A constructor for an argument which is not a boolean switch.
     */
    ClapArgument(std::string const & flag, std::string const & usageDescription, std::string const & longDescription, bool isRequired = true, bool isSwitch = false);
    
    /**
     *  A constructor for an argument which is a boolean switche.
     */
    ClapArgument(char flag, std::string const & usageDescription,  std::string const & longDescription, bool isRequired = true, bool isSwitch = true);
    
    /**
     *  A virtual destructor for an argument.
     */
    virtual ~ClapArgument();
    
    
    /**
     *  A save getter for the flag variable for internal use.
     *
     *  @return The flag.
     */
    std::string const & flag() const;
    
    /**
     *  A save getter for the hyphen variable for internal use.
     *
     *  @return The hypehen.
     */
    std::string const & hyphen() const;
    
    /**
     *  A save getter for the isRequired variable for internal use.
     *
     *  @return True, if the variable is required.
     */
    bool isRequired() const;
    
    /**
     *  A save getter for the isSwitch variable for internal use.
     *
     *  @return True, if the argument is a switch.
     */
    bool isSwitch() const;
    
    /**
     *  A save getter for the isSwitch variable for internal use.
     *
     *  @return True, if the value was set.
     */
    bool isSet() const;
    
    /**
     *  A save getter for the description variable for internal use.
     *
     *  @return The long description.
     */
    std::string const & longDescription() const;
    

    /**
     *  A save getter for the usage description.
     *
     *  @return The usage information.
     */
    std::string const & usageDescription() const;
    
    
    /**
     *  A virtual function which needs to be implemented for every subclass which
     *  sets a value read from the command line to the argument.
     *
     *  @param valueRead The value read from the command line as string.
     */
    virtual void setValue(std::string const & valueRead)=0;
  };

}
#endif
