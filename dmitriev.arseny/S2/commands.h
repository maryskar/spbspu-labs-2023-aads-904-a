#ifndef COMMANDS_H
#define COMMANDS_H

#include "dictionary.h"
#include <sstream>

namespace dmitriev
{
  void printDataset(const Dictionary< std::string, Dictionary< int, std::string > >& dicOfDic,
    std::istream& inp, std::ostream& out);

  void complementDataset(Dictionary< std::string, Dictionary< int, std::string > >& dicOfDic,
    std::istream& inp);
  void intersectDataset(Dictionary< std::string, Dictionary< int, std::string > >& dicOfDic,
    std::istream& inp);
  void unionDataset(Dictionary< std::string, Dictionary< int, std::string > >& dicOfDic,
    std::istream& inp);
}

#endif
