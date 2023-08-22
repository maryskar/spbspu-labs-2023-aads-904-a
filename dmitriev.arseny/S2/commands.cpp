#include "commands.h"

void printDataset(const dmitriev::Dictionary< std::string, dmitriev::Dictionary< int, std::string > >& dicOfDic, std::istream& inp, std::ostream& out)
{
  std::string line;
  std::getline(inp, line);
  std::stringstream ss(line);
  std::string name = "";

  ss >> name;

  if (!ss)
  {
    throw std::out_of_range("incorrect inp");
  }
  if (dicOfDic.at(name).isEmpty())
  {
    out << "<EMPTY>";
    return;
  }

  std::cout << name;
  typename  dmitriev::Dictionary< int, std::string >::constIterator it;
  for (it = dicOfDic.at(name).constBegin(); it != dicOfDic.at(name).constEnd(); it++)
  {
    out << ' ' << it->first << ' ' << it->second;
  }
}

void complementDataset(dmitriev::Dictionary< std::string, dmitriev::Dictionary< int, std::string > >& dicOfDic, std::istream& inp)
{
  std::string line;
  std::getline(inp, line);
  std::stringstream ss(line);

  std::string newName = "";
  std::string lhsName = "";
  std::string rhsName = "";

  ss >> newName >> lhsName >> rhsName;

  if (!ss)
  {
    throw std::out_of_range("incorrect inp");
  }

  dicOfDic.insert({newName, dmitriev::complementDictionary(dicOfDic.at(lhsName), dicOfDic.at(rhsName))});
}
void intersectDataset(dmitriev::Dictionary< std::string, dmitriev::Dictionary< int, std::string > >& dicOfDic, std::istream& inp)
{
  std::string line;
  std::getline(inp, line);
  std::stringstream ss(line);

  std::string newName = "";
  std::string lhsName = "";
  std::string rhsName = "";

  ss >> newName >> lhsName >> rhsName;

  if (!ss)
  {
    throw std::out_of_range("incorrect inp");
  }

  dicOfDic.insert({newName, dmitriev::intersectDictionary(dicOfDic.at(lhsName), dicOfDic.at(rhsName))});
}
void unionDataset(dmitriev::Dictionary< std::string, dmitriev::Dictionary< int, std::string > >& dicOfDic, std::istream& inp)
{
  std::string line;
  std::getline(inp, line);
  std::stringstream ss(line);

  std::string newName = "";
  std::string lhsName = "";
  std::string rhsName = "";

  ss >> newName >> lhsName >> rhsName;

  if (!ss)
  {
    throw std::out_of_range("incorrect inp");
  }

  dicOfDic.insert({newName, dmitriev::unionDictionary(dicOfDic.at(lhsName), dicOfDic.at(rhsName))});
}
