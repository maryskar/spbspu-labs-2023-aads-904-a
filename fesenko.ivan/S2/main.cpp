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
  using dictionary = fesenko::Dictionary< int, std::string, std::less< > >;
  using dict_of_dict = fesenko::Dictionary< std::string, dictionary, std::less< std::string > >;
  dict_of_dict container = fesenko::genDictOfDicts< dict_of_dict, dictionary >(in);
  try {
    while (std::cin) {
      std::string command;
      std::cin >> command;
      if (!std::cin) {
        break;
      }
      if (command == "print") {
        std::string name;
        std::cin >> name;
        fesenko::print(std::make_pair(name, container.at(name)), std::cout);
        std::cout << "\n";
      } else {
        std::string newDictName;
        std::string dictName1;
        std::string dictName2;
        std::cin >> newDictName >> dictName1 >> dictName2;
        dictionary dict1 = container.at(dictName1);
        dictionary dict2 = container.at(dictName2);
        dictionary newDict;
        if (command == "complement") {
          newDict = make_complementation(dict1, dict2);
        } else if (command == "intersect") {
          newDict = make_intersection(dict1, dict2);
        } else if (command == "union") {
          newDict = make_union(dict1, dict2);
        } else {
          fesenko::outInvalidCommandMessage(std::cout);
          std::cout << "\n";
          continue;
        }
        if (container.insert(std::make_pair(newDictName, newDict)).second == false) {
          auto it = container.find(newDictName);
          container.at(it->first) = newDict;
        }
      }
    }
  } catch (...) {
    fesenko::outInvalidCommandMessage(std::cout);
    std::cout << "\n";
  }
}
