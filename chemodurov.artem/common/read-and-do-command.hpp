#ifndef S2_READ_AND_DO_COMMAND_HPP
#define S2_READ_AND_DO_COMMAND_HPP
#include <map/create-command-dictionary.hpp>

namespace chemodurov
{
  std::string readCommand(std::istream & in);
  void doCommand(const std::string & name_command,
      const std::pair< Map< std::string, union_t >, Map< std::string, print_t > > & commands,
        Map< std::string, dic_t > & data,
      std::istream & in,
      std::ostream & out);
}

#endif
