#include <iostream>
#include <fstream>
#include <utility>
#include <dictionary/dictionary.h>
#include <commands.h>
#include "genDictOfDicts.h"

int main(int argc, char *argv[])
{
  if (argc != 2) {
    std::cerr << "Invalid number of arguments\n";
    return 2;
  }
  std::ifstream in(argv[1]);
  if (!in.is_open()) {
    std::cerr << "Can`t open the file\n";
    return 2;
  }
  using dict = fesenko::Dictionary< int, std::string, std::less< > >;
  using dict_of_dict = fesenko::Dictionary< std::string, dict, std::less< std::string > >;
  using dict_c = fesenko::Dictionary< std::string, dict (*)(const dict &, const dict &), std::less< > >;
  dict_of_dict container = fesenko::genDictOfDicts< dict_of_dict, dict >(in);
  dict_c commands;
  commands.insert(std::make_pair("complement", fesenko::make_complementation< dict >));
  commands.insert(std::make_pair("intersect", fesenko::make_intersection< dict >));
  commands.insert(std::make_pair("union", fesenko::make_union< dict >));
  while (std::cin) {
    std::string command;
    std::cin >> command;
    if (!std::cin) {
      break;
    }
    try {
      if (command == "print") {
        std::string name;
        std::cin >> name;
        fesenko::print(std::make_pair(name, container.at(name)), std::cout);
        std::cout << "\n";
      } else {
        auto func = commands.at(command);
        std::string newDictName;
        std::string dictName1;
        std::string dictName2;
        std::cin >> newDictName >> dictName1 >> dictName2;
        dict dict1 = container.at(dictName1);
        dict dict2 = container.at(dictName2);
        dict newDict = func(dict1, dict2);
        if (!container.insert(std::make_pair(newDictName, newDict)).second) {
          auto it = container.find(newDictName);
          container.at(it->first) = newDict;
        }
      }
    } catch (...) {
      fesenko::outInvalidCommandMessage(std::cout);
      std::cout << "\n";
    }
  }
}
