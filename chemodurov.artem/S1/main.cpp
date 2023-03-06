#include <iostream>
#include <fstream>

int main(int argc, char ** argv)
{
  if (argc != 1 && argc != 2)
  {
    std::cerr << "Error\n";
    return 1;
  }
  std::string line;
  if (argc == 1)
  {
    std::getline(std::cin, line);
  }
  else
  {
    std::ifstream input;
    if (!input)
    {
      std::cerr << "Error while reading\n";
      return 1;
    }
    std::getline(input, line);
  }
  return 0;
}