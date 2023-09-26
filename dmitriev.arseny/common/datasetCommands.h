#ifndef COMMANDS_H
#define COMMANDS_H

#include <iostream>
#include "outputOfSpecialMessages.h"
#include "dictionary.h"
#include "AVL.h"

namespace dmitriev
{
  template< typename inputIterator >
  void printDataset(inputIterator first,
    inputIterator last,
    std::string name,
    std::ostream& out)
  {
    out << name;

    for (; first != last; first++)
    {
      out << ' ' << first->first << ' ' << first->second;
    }
  }

  template< typename dataset >
  void complementDataset(dataset& dataSet,
    std::string name, std::string lhsName, std::string rhsName)
  {
    dataSet[name] = complementDictionary(dataSet.at(lhsName), dataSet.at(rhsName));
  }
  template< typename dataset >
  void intersectDataset(dataset& dataSet,
    std::string name, std::string lhsName, std::string rhsName)
  {
    dataSet[name] = intersectDictionary(dataSet.at(lhsName), dataSet.at(rhsName));
  }
  template< typename dataset >
  void unionDataset(dataset& dataSet,
    std::string name, std::string lhsName, std::string rhsName)
  {
    dataSet[name] = unionDictionary(dataSet.at(lhsName), dataSet.at(rhsName));
  }
}

#endif
