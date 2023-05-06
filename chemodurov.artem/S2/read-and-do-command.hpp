#ifndef S2_READ_AND_DO_COMMAND_HPP
#define S2_READ_AND_DO_COMMAND_HPP
#include "create-command-dictionary.hpp"

namespace chemodurov
{
  void readAndDoCommand(std::istream & in, std::ostream & out, const Dictionary< std::string, command_t > & commands,
      Dictionary< std::string, dic_t > & data);
}

#endif
