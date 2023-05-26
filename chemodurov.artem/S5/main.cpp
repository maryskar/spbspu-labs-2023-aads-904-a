#include <iostream>
#include <fstream>
#include <cstring>
#include <create-command-dictionary.hpp>
#include "read-map-of-int-string.hpp"
#include "printer.hpp"

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
  chemodurov::Printer pr(std::cout);
  if (data.empty())
  {
    chemodurov::outEmpty(std::cout);
  }
  else if (!std::strcmp(argv[1], "ascending"))
  {
    data.traverse_lnr(pr);
  }
  else if (!std::strcmp(argv[1], "descending"))
  {
    data.traverse_rnl(pr);
  }
  else
  {
    data.traverse_breadth(pr);
  }
  std::cout << '\n';
  return 0;
}
