#include <iostream>
#include <fstream>
#include "Dictionary.h"
#include "commands.h"
#include "getDictFromInput.h"
#include <string>

int main(int argc, char* argv[])
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
  using dict = aksenov::Dictionary< int, std::string, std::less< > >;
  using dictOfDicts = aksenov::Dictionary< std::string, dict, std::less< > >;
  dictOfDicts bigData = aksenov::getDictFromInput< dictOfDicts, dict >(inputFile);
  while (std::cin.good())
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
      aksenov::print(std::make_pair(name, bigData.at(name)), std::cout);
    }
    else if (command == "complement")
    {
      std::string newName;
      std::string dictName1;
      std::string dictName2;
      std::cin >> newName >> dictName1 >> dictName2;
      dict dict1 = bigData.at(dictName1);
      dict dict2 = bigData.at(dictName2);
      dict resDict = aksenov::doComplement(dict1, dict2);
      if (!bigData.insert(std::make_pair(newName, resDict)).second)
      {
        auto it = bigData.find(newName);
        bigData.at(it->first) = resDict;
      }
    }
  }
  return 0;
}
