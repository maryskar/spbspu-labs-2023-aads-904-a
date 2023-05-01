#include <iostream>
#include <fstream>
#include <algorithm>
#include "dictionary.hpp"

int main(int argc, char ** argv)
{
  if (argc != 2)
  {
    std::cerr << "There is no file in parameters\n";
    return 1;
  }
  std::ifstream input(argv[1]);
  if (!input.is_open())
  {
    std::cerr << "The file doesn't opened\n";
    return 1;
  }
  chemodurov::Dictionary< int, std::string, std::less< > > dic1 = { std::pair< int, std::string >{5, "abc"} };
  chemodurov::Dictionary< int, std::string, std::less< > > dic2 = { std::pair< int, std::string >{4, "abc"} };
  dic1 = { std::pair< int, std::string >{4, "abc"} };
  std::cout << dic1.begin()->first;
  return 0;
}
