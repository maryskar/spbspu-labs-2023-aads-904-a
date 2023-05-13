#include "read-and-do-command.hpp"

namespace chemodurov
{
  void doCommand(const std::string & name_command,
    const Dictionary< std::string, command_t > & commands,
    std::istream & in, std::ostream & out,
    Dictionary< std::string, dic_t > & data)
  {
    (commands.at(name_command))(in, out, data);
  }

  std::string readCommand(std::istream & in)
  {
    std::string name_command;
    in >> name_command;
    if (!in)
    {
      throw std::logic_error("Error");
    }
    return name_command;
  }
}
