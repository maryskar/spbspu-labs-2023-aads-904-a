#include "read-and-do-command.hpp"
#include <iostream>

namespace chemodurov
{
  void doCommand(const std::string & name_command,
      const std::pair< Dictionary< std::string, union_t >, Dictionary< std::string, print_t > > & commands,
      Dictionary< std::string, dic_t > & data,
      std::istream & in,
      std::ostream & out)
  {
    using namespace std::placeholders;
    try
    {
      (std::bind(commands.first.at(name_command), std::ref(in), _1))(data);
    }
    catch (const std::out_of_range & e)
    {
      (std::bind(commands.second.at(name_command), std::ref(in), std::ref(out), _1))(data);
    }
  }

  std::string readCommand(std::istream & in)
  {
    std::string name_command;
    in >> name_command;
    if (!in)
    {
      throw std::runtime_error("Error");
    }
    return name_command;
  }
}
