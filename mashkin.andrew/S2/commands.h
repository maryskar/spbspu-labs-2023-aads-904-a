#ifndef S2_COMMANDS_H
#define S2_COMMANDS_H
#include <iostream>
#include <string>
#include <IOstreamOverloads.h>
#include "dictionary.h"

namespace mashkin
{
  void print(std::istream& inp, Dictionary< std::string, Dictionary< int, std::string > >& dicts);
  void complement(std::istream& inp, Dictionary< std::string, Dictionary< int, std::string > >& dicts);
  void intersect(std::istream& inp, Dictionary< std::string, Dictionary< int, std::string > >& dicts);
  void unionDicts(std::istream& inp, Dictionary< std::string, Dictionary< int, std::string > >& dicts);
}
#endif
