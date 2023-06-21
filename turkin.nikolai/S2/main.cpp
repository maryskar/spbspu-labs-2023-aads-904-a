#include <iostream>
#include <fstream>
#include <string>
#include <cstddef>
#include <functional>
#include "dictionary.hpp"
#include "forward-list.hpp"

int main(int argc, char * argv[])
{
  if (argc == 1)
  {
    std::cerr << "no file\n";
    return 1;
  }

  std::ifstream file;
  file.open(argv[1]);
  if (!file.is_open())
  {
    std::cerr << "cannot open file\n";
    return 1;
  }

  turkin::Dictionary< std::size_t, std::string, std::less< > > dict;

  while (file)
  {
    std::size_t key;
    std::string value;
    file >> key >> value;
    std::cout << line << "\n";
  }

  return 0;
}
