#include <iostream>
#include <fstream>
#include <string>
#include "TreeDict.h"
#include "CommandsS2.h"
#include "StreamProcessingS2.h"
#include "printMessages.h"

int main(int argc, char** argv)
{
  using Dict = skarlygina::TreeDict< int, std::string >;
  using AllDicts = skarlygina::TreeDict< std::string, Dict >;
  if (argc == 1)
  {
    skarlygina::printNoFileToRead(std::cerr);
    return 1;
  }
  std::ifstream fin(argv[1]);
  if (!fin.good())
  {
    skarlygina::printUnableToReadFile(std::cerr);
    return 1;
  }
  try
  {
    auto data = skarlygina::getDictsFromStream< Dict, AllDicts >(fin);
    fin.close();
    while (!std::cin.eof())
    {
      try
      {
        skarlygina::processCommand< Dict, AllDicts >(std::cin, std::cout, data);
      }
      catch (const std::invalid_argument&)
      {
        skarlygina::printInvalidCommand(std::cout);
      }
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << std::endl;
    return 2;
  }
  return 0;
}

