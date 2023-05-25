#include <iostream>
#include <fstream>
#include <cstring>

int main(int argc, char ** argv)
{
  if (argc != 3)
  {
    std::cerr << "Incorrect amount of CML args\n";
    return 1;
  }
  if (std::strcmp(argv[1], "ascending") != 0 && std::strcmp(argv[1], "decending") != 0 && std::strcmp(argv[1], "breadth") != 0)
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
  return 0;
}
