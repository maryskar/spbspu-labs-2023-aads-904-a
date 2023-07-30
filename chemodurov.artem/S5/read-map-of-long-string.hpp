#ifndef S5_READ_MAP_OF_LONG_STRING_HPP
#define S5_READ_MAP_OF_LONG_STRING_HPP
#include <iosfwd>
#include <map.hpp>

namespace chemodurov
{
  Map< long, std::string > readMapOfIntString(std::istream & in);
}

#endif
