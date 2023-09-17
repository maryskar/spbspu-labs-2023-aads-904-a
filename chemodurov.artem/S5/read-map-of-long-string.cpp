#include "read-map-of-long-string.hpp"
#include <iostream>

namespace chemodurov
{
  std::pair< long, std::string > readPair(std::istream & in)
  {
    long a = 0;
    in >> a;
    std::string str;
    in >> str;
    if (!in)
    {
      throw std::runtime_error("End of reading");
    }
    return {a, str};
  }

  Map< long, std::string > readMapOfIntString(std::istream & in)
  {
    Map< long, std::string > res;
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
