#include <cstddef>
#include <fstream>
#include <iostream>
#include "dictionary.h"
#include "forwardConstIterator.h"
#include "forwardIterator.h"
#include "forwardList.h"

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cerr << "Wrong number of arguments\n";
    return 1;
  }
  else
  {
    std::ifstream input;
    input.open(argv[1]);
    if (!input.is_open())
    {
      std::cerr << "Can't open file\n";
      return 1;
    }
    /*using dict = mashkin::Dictionary< int, std::string >;
    using dicts = mashkin::Dictionary< std::string, dict >;*/

  }
  return 0;
}
