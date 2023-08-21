#include <iostream>
#include <memory>
#include <limits>
#include "../S2/dict.h"
#include "murmurhash2.h"
#include "hashtable.h"
#include "commands.h"
#include "../common/printmessages.h"
int main()
{
  constexpr auto maxLLSize = std::numeric_limits< std::streamsize >::max();
  //std::vector< std::shared_ptr< romanovich::Dictionary< std::string, std::string>> > dicts;
  romanovich::HashTable table;
  auto commandDictionary = romanovich::createCommandDictionary(&table);
  while (std::cin)
  {
    std::string command;
    std::cin >> command;
    if (!std::cin)
    {
      break;
    }
    try
    {
      commandDictionary[command](std::cin, std::cout);
    }
    catch (...)
    {
      printInvalidCommand(std::cout) << '\n';
      std::cin.ignore(maxLLSize, '\n');
    }
  }
}
