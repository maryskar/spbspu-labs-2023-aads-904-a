#include "map.hpp"
#include <iostream>

namespace chemodurov
{
  void print(std::ostream & out, const std::pair< int, std::string > & pair)
  {
    out << pair.first << ' ' << pair.second;
  }

  void print(std::ostream & out, const Map< int, std::string > & dict)
  {
    auto end_ = dict.end();
    for (auto i = dict.begin(); i != end_; ++i)
    {
      if (i == dict.begin())
      {
        print(out, *i);
      }
      else
      {
        print(out << ' ', *i);
      }
    }
  }

  void print(std::ostream & out, const std::pair< std::string, Map< int, std::string > > & pair)
  {
    out << pair.first << ' ';
    print(out, pair.second);
  }
}
