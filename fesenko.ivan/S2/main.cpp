#include <iostream>
#include <fstream>
#include "dictionary.h"
#include "dictionaryCommands.h"

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
  using dictionary_elem = std::pair< int, std::string >;
  using dict_of_dict = fesenko::Dictionary< std::string, dictionary, std::less< std::string > >;
  using dict_of_dict_elem = std::pair < std::string, dictionary >;
  dict_of_dict container;
  try {
    while (in) {
      std::string name;
      in >> name;
      if (!in) {
        break;
      }
      dictionary dict;
      int key = 0;
      std::string value;
      while (in) {
        in >> key >> value;
        if (!in) {
          break;
        }
        dict.insert(dictionary_elem(key, value));
      }
      in.clear();
      container.insert(dict_of_dict_elem(name, dict));
    }
  } catch (const std::exception &e) {
    std::cerr << e.what() << "\n";
    return 2;
  }
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
        fesenko::print(dict_of_dict_elem(name, container.at(name)), std::cout);
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
          continue;
        }
        if (container.insert(dict_of_dict_elem(newDictName, newDict)).second == false) {
          auto it = container.find(newDictName);
          container.at(it->first) = newDict;
        }
      }
    }
  } catch (...) {
    fesenko::outInvalidCommandMessage(std::cout);
  }
}
