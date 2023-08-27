#include "datasetCommands.h"

namespace dmitriev
{
  void printDataset(const Dictionary< std::string, Dictionary< int, std::string > >& dataSet,
    std::string name, std::ostream& out)
  {
    if (dataSet.at(name).isEmpty())
    {
      out << "<EMPTY>";
      return;
    }

    out << name;
    typename Dictionary< int, std::string >::constIterator it;
    for (it = dataSet.at(name).constBegin(); it != dataSet.at(name).constEnd(); it++)
    {
      out << ' ' << it->first << ' ' << it->second;
    }
  }

  void complementDataset(Dictionary< std::string, Dictionary< int, std::string > >& dataSet,
    std::string name, std::string lhsName, std::string rhsName)
  {
    dataSet[name] = complementDictionary(dataSet.at(lhsName), dataSet.at(rhsName));
  }
  void intersectDataset(Dictionary< std::string, Dictionary< int, std::string > >& dataSet,
    std::string name, std::string lhsName, std::string rhsName)
  {
    dataSet[name] = intersectDictionary(dataSet.at(lhsName), dataSet.at(rhsName));
  }
  void unionDataset(Dictionary< std::string, Dictionary< int, std::string > >& dataSet,
    std::string name, std::string lhsName, std::string rhsName)
  {
    dataSet[name] = unionDictionary(dataSet.at(lhsName), dataSet.at(rhsName));
  }
}
