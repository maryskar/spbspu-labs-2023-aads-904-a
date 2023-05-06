#include "create-command-dictionary.hpp"

namespace chemodurov
{
  void print(std::istream & in, std::ostream & out, Dictionary< std::string, dic_t > & data)
  {
    std::string name = "";
    in >> name;
    Dictionary< std::string, dic_t >::iterator it = data.find(name);
    if (!in || it == data.end())
    {
      throw std::invalid_argument("Invalid command");
    }
    out << *(++it) << '\n';
  }
}
