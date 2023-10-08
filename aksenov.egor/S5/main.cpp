#include <iostream>
#include <limits>
#include <fstream>
#include <string>
#include <AVL/AVL.h>

int main(int args, char *argv[])
{
  std::ifstream inp;
  if (argc == 3)
  {
    inputFile.open(argv[2]);
    if (!inputFile.is_open())
    {
      std::cerr << "Cannot open file\n";
      return 1;
    }
  }
  else
  {
    std::cerr << "Wrong number of args\n";
    return 1;
  }

}
