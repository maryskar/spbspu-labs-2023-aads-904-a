#include "read-map-of-int-string.hpp"
#include <iostream>

namespace chemodurov
{
  std::pair< int, std::string > readPair(std::istream & in)
  {
    int a = 0;
    in >> a;
    std::string str;
    in >> str;
    if (!in)
    {
      throw std::runtime_error("End of reading");
    }
    return {a, str};
  }

  Map< int, std::string > readMapOfIntString(std::istream & in)
  {
    Map< int, std::string > res;
    try
    {
      while (in)
      {
        res.insert(readPair(in));
      }
    }
    catch (...)
    {}
    return res;
  }
}
