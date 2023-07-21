#include "getInputStream.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

std::istream& potapova::getInputStream(int argc, char** argv)
{
  if (argc == 2)
  {
    static std::ifstream input_file;
    input_file.open(argv[1]);
    if (!input_file.is_open())
    {
      throw std::runtime_error("Failed to open file");
    }
    return input_file;
  }
  if (argc > 2)
  {
    throw std::logic_error("Incorrect number of arguments");
  }
  return std::cin;
}
