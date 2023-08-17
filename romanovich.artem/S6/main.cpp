#include <iostream>
#include <algorithm>
#include "sorttest.h"
int main(int argc, char *argv[])
{
  if (argc != 4)
  {
    std::cerr << "Invalid arguments number.\n";
    return 1;
  }
  size_t size = std::strtoull(argv[3], nullptr, 10);
  if (size == 0)
  {
    std::cerr << "Empty sequence.";
    return 2;
  }
  std::string sortOrder = argv[1];
  std::string dataType = argv[2];
  try
  {
    if (dataType != "ints" && dataType != "floats")
    {
      std::cerr << "Invalid data type.";
      return 2;
    }
    if (dataType == "ints")
    {
      std::vector< int > data = romanovich::generateRandomInts(size, 1, 10);
      romanovich::runTest< int >(data, size, sortOrder);
    }
    if (dataType == "floats")
    {
      std::vector< float > data = romanovich::generateRandomFloats(size, 1, 10);
      romanovich::runTest< float >(data, size, sortOrder);
    }
  }
  catch (...)
  {
    std::cerr << "Error while sorting.";
    return 2;
  }
  return 0;
}
