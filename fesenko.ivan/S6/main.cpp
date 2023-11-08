#include <iostream>
#include <avl/AVL.h>
#include <commands.h>
#include "makeSorts.h"

int main(int argc, char *argv[])
{
  if (argc != 4) {
    std::cerr << "Invalid number of arguments\n";
    return 2;
  }
  fesenko::AVL< std::string, void (*)(size_t, std::ostream &), std::less< > > sorts;
  sorts.insert(std::make_pair("ascending ints", fesenko::makeSorts< int, std::less< > >));
  sorts.insert(std::make_pair("ascending floats", fesenko::makeSorts< float, std::less< > >));
  sorts.insert(std::make_pair("descending ints", fesenko::makeSorts< int, std::greater< > >));
  sorts.insert(std::make_pair("descending floats", fesenko::makeSorts< float, std::greater< > >));
  try {
    size_t number = std::stoull(argv[3]);
    std::string parameter = argv[1];
    std::string type = argv[2];
    sorts.at(parameter + " " + type)(number, std::cout);
  } catch (...) {
    fesenko::outInvalidCommandMessage(std::cout);
    std::cout << "\n";
    return 2;
  }
}
