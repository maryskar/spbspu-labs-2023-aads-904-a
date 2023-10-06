#include <iostream>
#include <utility>
#include <fstream>
#include <string>
#include "nonBalancedBinarySearchTree.h"
#include "commands.h"
//#include "getDictFromInput.h"
template< typename DictOfDicts, typename Dict >
DictOfDicts getDictFromInput(std::istream &in)
{
  DictOfDicts res;
  while (in)
  {
    std::string name = "";
    in >> name;
    if (!in || name == "stop")
    {
      break;
    }
    Dict data;
    std::string val = "";
    int key = 0;
    while (in)
    {
      in >> key >> val;
      if (!in)
      {
        break;
      }
      data.insert(std::make_pair(key, val));
    }
    in.clear();
    res.insert(std::make_pair(name, data));
  }
  return res;
}



int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cerr << "error" << "\n";
    return 1;
  }
  std::ifstream inputFile(argv[1]);
  if (!inputFile.is_open())
  {
    std::cerr << "Cannot open file: " << "\n";
    return 1;
  }
  using dict = aksenov::BST< int, std::string, std::less< > >;
  using dictOfDicts = aksenov::BST< std::string, dict, std::less< > >;
  dictOfDicts bigData = getDictFromInput< dictOfDicts, dict >(inputFile);
  aksenov::commandMap commands;
  aksenov::createCommandDict(commands);
  while (std::cin.good())
  {
    try
    {
      std::string command;
      std::cin >> command;
      if (!std::cin)
      {
        break;
      }
      if (command == "print")
      {
        std ::string name;
        std::cin >> name;
        aksenov::print(name,bigData.at(name), std::cout);
        std::cout << "\n";
      }
      else
      {
        std::string newName;
        std::string dictName1;
        std::string dictName2;
        std::cin >> newName >> dictName1 >> dictName2;
        dict dict1 = bigData.at(dictName1);
        dict dict2 = bigData.at(dictName2);
        dict resDict = commands[command](dict1, dict2);
        if (!bigData.insert(std::make_pair(newName, resDict)).second)
        {
          auto it = bigData.find(newName);
          bigData.at(it->first) = resDict;
        }
      }
    }
    catch (const std::invalid_argument &e)
    {
      std::cout << "<EMPTY>" << "\n";
    }
    catch (...)
    {
      std::cout << "<INVALID COMMAND>" << "\n";
    }
  }
  return 0;
}

