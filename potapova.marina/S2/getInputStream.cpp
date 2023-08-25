#include "getInputStream.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

std::istream* potapova::getInputStream(const int argc, const char* const* const argv)
{
  if (argc == 2)
  {
    static std::ifstream input_file;
    input_file.open(argv[1]);
    if (!input_file.is_open())
    {
      throw std::ifstream::failure("Failed to open file");
    }
    return &input_file;
  }
  if (argc > 2)
  {
    throw std::logic_error("Incorrect number of arguments");
  }
  return &std::cin;
}
