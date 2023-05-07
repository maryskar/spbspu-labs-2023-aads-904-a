#include "read-and-do-command.hpp"

namespace chemodurov
{
  void readAndDoCommand(std::istream & in, std::ostream & out, const Dictionary< std::string, command_t > & commands,
      Dictionary< std::string, dic_t > & data)
  {
    std::string name_command;
    in >> name_command;
    if (!in)
    {
      throw std::logic_error("Error");
    }
    Dictionary< std::string, command_t >::const_iterator cit = commands.find(name_command);
    if (cit == commands.clast())
    {
      throw std::invalid_argument("Invalid command");
    }
    ++cit;
    cit->second(in, out, data);
  }
}
