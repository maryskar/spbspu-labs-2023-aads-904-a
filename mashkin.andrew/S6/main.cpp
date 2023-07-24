#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <AVL.h>
#include <string>

int main(int argc, char** argv)
{
  if (argc != 4)
  {
    std::cerr << "Wrong number of arguments\n";
    return 1;
  }
  char* end{};
  size_t nimbOfNumbers = std::strtol(argv[3], &end, 10);
  mashkin::AVL< std::string, mashkin::AVL< std::string, void (*)(std::ostream&, size_t) > > dict;
  if (dict.contains(argv[1]))
  {
    if (dict[argv[1]].contains(argv[2]))
    {
      dict[argv[1]][argv[2]](std::cout, nimbOfNumbers);
    }
    else
    {
      std::cerr << "Incorrect argument\n";
      return 0;
    }
  }
  else
  {
    std::cerr << "Incorrect argument\n";
    return 0;
  }
  return 0;
}
