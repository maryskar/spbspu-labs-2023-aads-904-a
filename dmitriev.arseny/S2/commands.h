#ifndef COMMANDS_H
#define COMMANDS_H

#include "dictionary.h"

namespace dmitriev
{
  void printDataset(const dmitriev::Dictionary< std::string, dmitriev::Dictionary< int, std::string > >& dicOfDic, std::istream& inp, std::ostream& out);

  void complementDataset(dmitriev::Dictionary< std::string, dmitriev::Dictionary< int, std::string > >& dicOfDic, std::istream& inp);
  void intersectDataset(dmitriev::Dictionary< std::string, dmitriev::Dictionary< int, std::string > >& dicOfDic, std::istream& inp);
  void unionDataset(dmitriev::Dictionary< std::string, dmitriev::Dictionary< int, std::string > >& dicOfDic, std::istream& inp);
}

#endif
