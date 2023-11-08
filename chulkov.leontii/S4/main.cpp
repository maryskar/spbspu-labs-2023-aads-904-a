#include <iostream>
#include <fstream>
#include <string>
#include "TreeDict.h"
#include "StreamProcessing.h"
#include "printMessages.h"

int main(int argc, char** argv)
{
  using Dict = chulkov::TreeDict< int, std::string >;
  using AllDicts = chulkov::TreeDict< std::string, Dict >;
  if (argc == 1)
  {
    chulkov::printNoFileToRead(std::cerr);
    return 1;
  }
  std::ifstream fin(argv[1]);
  if (!fin.good())
  {
    chulkov::printUnableToReadFile(std::cerr);
    return 1;
  }
  try
  {
    auto data = chulkov::getDictsFromStream< Dict, AllDicts >(fin);
    fin.close();
    while (!std::cin.eof())
    {
      try
      {
        chulkov::processCommand< Dict, AllDicts >(std::cin, std::cout, data);
      }
      catch (const std::invalid_argument&)
      {
        chulkov::printInvalidCommand(std::cout);
      }
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 2;
  }
  return 0;
}
