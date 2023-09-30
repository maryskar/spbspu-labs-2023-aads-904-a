#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <AVL/AVL.h>
#include "createMapOfSortFunctions.h"

int main(int argc, char** argv)
{
  if (argc != 4)
  {
    std::cerr << "Wrong number of arguments\n";
    return 1;
  }
  char* end{};
  size_t numbOfNumbers = std::strtol(argv[3], &end, 10);
  if (numbOfNumbers == 0)
  {
    std::cerr << "Empty sequence\n";
    return 1;
  }
  mashkin::AVL< std::string, mashkin::AVL< std::string, void (*)(std::ostream&, size_t) > > map;
  map = mashkin::createMapOfSortFunctions();
  if (map.contains(argv[1]))
  {
    if (map[argv[1]].contains(argv[2]))
    {
      map[argv[1]][argv[2]](std::cout, numbOfNumbers);
    }
    else
    {
      std::cerr << "Incorrect argument\n";
      return 1;
    }
  }
  else
  {
    std::cerr << "Incorrect argument\n";
    return 1;
  }
  return 0;
}
