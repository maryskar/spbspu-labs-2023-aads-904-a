#ifndef READ_DICT_H
#define READ_DICT_H
#include <string>
#include "dictionary.h"

namespace kryuchkova
{
  Dictionary< std::string, Dictionary< int, std::string, std::less< > >, std::less< > > readDictOfDict(std::istream & in);
}

#endif