#include <iostream>
#include <fstream>
#include <cstring>
#include "read-map-of-int-string.hpp"

bool checkArg(const char * arg)
{
  return !std::strcmp(arg, "ascending") || !std::strcmp(arg, "descending") || !std::strcmp(arg, "breadth");
}

int main(int argc, char ** argv)
{
  if (argc != 3)
  {
    std::cerr << "Incorrect amount of CML args\n";
    return 1;
  }
  if (!checkArg(argv[1]))
  {
    std::cerr << "Incorrect first CML arg\n";
    return 1;
  }

  std::ifstream input(argv[2]);
  if (!input.is_open())
  {
    std::cerr << "The file doesn't opened\n";
    return 1;
  }
  chemodurov::Map< int, std::string > data = chemodurov::readMapOfIntString(input);

  return 0;
}
