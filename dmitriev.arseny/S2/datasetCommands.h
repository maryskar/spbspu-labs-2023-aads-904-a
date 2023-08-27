#ifndef COMMANDS_H
#define COMMANDS_H

#include "dictionary.h"
#include <iostream>

namespace dmitriev
{
  void printDataset(const Dictionary< std::string, Dictionary< int, std::string > >& dataSet,
    std::string name, std::ostream& out);

  void complementDataset(Dictionary< std::string, Dictionary< int, std::string > >& dataSet,
    std::string name, std::string lhsName, std::string rhsName);
  void intersectDataset(Dictionary< std::string, Dictionary< int, std::string > >& dataSet,
    std::string name, std::string lhsName, std::string rhsName);
  void unionDataset(Dictionary< std::string, Dictionary< int, std::string > >& dataSet,
    std::string name, std::string lhsName, std::string rhsName);
}

#endif
