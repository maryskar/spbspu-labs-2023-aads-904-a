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
//    if (dataType == "ints")
//    {
      runTest(size);
//    }
//    else if (dataType == "floats")
//    {
//      //runTest< float >(size);
//    }
//    else
//    {
//      std::cerr << "Invalid data type.";
//      return 2;
//    }
  }
  catch (...)
  {
    std::cerr << "Error while sorting ints.";
    return 2;
  }
  return 0;
}
