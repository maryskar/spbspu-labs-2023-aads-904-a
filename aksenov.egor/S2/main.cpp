#include <iostream>
#include <fstream>
#include <string>
#include <Dictionary.h>
#include <commands.h>
#include <getDictFromInput.h>

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
  using dict = aksenov::Dictionary< int, std::string, std::less< > >;
  using dictOfDicts = aksenov::Dictionary< std::string, dict, std::less< > >;
  dictOfDicts bigData = aksenov::getDictFromInput< dictOfDicts, dict >(inputFile);
  using commandMap = aksenov::Dictionary< std::string, dict(*)(const dict &, const dict &) >;
  commandMap commands;
  aksenov::createCommandDict< commandMap >(commands);
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
        aksenov::print(name, bigData.at(name), std::cout);
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

