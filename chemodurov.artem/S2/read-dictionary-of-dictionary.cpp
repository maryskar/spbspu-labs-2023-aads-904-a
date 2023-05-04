#include "read-dictionary-of-dictionary.hpp"

using dic_t = chemodurov::Dictionary< int, std::string, std::less< > >;

namespace chemodurov
{
  dic_t readDicOfIntString(std::istream & in)
  {

  }
}

chemodurov::Dictionary< std::string, dic_t, std::less<> > chemodurov::readDictionaryOfDictionary(std::istream & in)
{

}
