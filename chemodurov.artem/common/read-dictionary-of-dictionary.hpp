#ifndef S2_READ_DICTIONARY_OF_DICTIONARY_HPP
#define S2_READ_DICTIONARY_OF_DICTIONARY_HPP
#include <string>
#include <map/map.hpp>

namespace chemodurov
{
  Map< std::string, Map< int, std::string, std::less< > >, std::less< > > readDictionaryOfDictionary(std::istream & in);
}

#endif
