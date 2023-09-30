#include "read_trash.h"

std::istream& tarasenko::readTrash(std::istream& input)
{
  input.clear();
  std::string trash = " ";
  getline(input, trash);
  return input;
}
