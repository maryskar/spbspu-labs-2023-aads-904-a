#include "dictionary.hpp"
#include <iostream>

namespace chemodurov
{
  void print(std::ostream & out, const Dictionary< int, std::string > & dict)
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

  void print(std::ostream & out, const std::pair< std::string, Dictionary< int, std::string > > & pair)
  {
    out << pair.first << ' ';
    print(out, pair.second);
  }
}
