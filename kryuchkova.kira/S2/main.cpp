#include <iostream>
#include <fstream>
#include "dictionary.h"
#include "dict_command.h"

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cerr << "invalid number of args\n";
    return 2;
  }
  std::ifstream in(argv[1]);
  if (!in.is_open())
  {
    std::cerr << "file open error\n";
    return 2;
  }

}