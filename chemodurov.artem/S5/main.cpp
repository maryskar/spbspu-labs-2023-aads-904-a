#include <iostream>
#include <fstream>
#include <cstring>
#include <create-command-dictionary.hpp>
#include "read-map-of-int-string.hpp"
#include "create-args-map.hpp"

int main(int argc, char ** argv)
{
  if (argc != 3)
  {
    std::cerr << "Incorrect amount of CML args\n";
    return 1;
  }

  std::ifstream input(argv[2]);
  if (!input.is_open())
  {
    std::cerr << "The file doesn't opened\n";
    return 1;
  }
  chemodurov::Map< int, std::string > data = chemodurov::readMapOfIntString(input);
  chemodurov::Printer pr(std::cout);
  auto args = chemodurov::createArgsMap();
  if (data.empty())
  {
    chemodurov::outEmpty(std::cout);
  }
  else
  {
    try
    {
      (data.*args.at(argv[1]))(pr);
    }
    catch (const std::out_of_range & e)
    {
      std::cerr << "Unexpected argument\n";
      return 1;
    }
  }
  std::cout << '\n';
  return 0;
}
