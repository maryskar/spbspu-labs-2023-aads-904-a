#include <iostream>
#include <fstream>
#include "Dictionary.h"
#include "commands.h"
#include "getDictFromInput.h"
#include <string>

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "error" << "\n";
    return 1;
  }
  std::ifstream inputFile(argv[1]);
  if (!inputFile.is_open())
  {
    std::cerr << "Cannot open file: " << "\n";
    return 1;
  }
  using dict = aksenov::Dictionary< int, std::string, std::less< > >;
  using dictOfDicts = aksenov::Dictionary< std::string, dict, std::less< > >;
  dictOfDicts bigData = aksenov::getDictFromInput< dictOfDicts, dict >(inputFile);
  return 0;
}
