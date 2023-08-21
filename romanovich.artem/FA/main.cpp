#include <iostream>
#include <memory>
#include "../S2/dict.h"
#include "murmurhash2.h"
#include "hashtable.h"
int main()
{
  std::vector< std::shared_ptr< romanovich::Dictionary< std::string, std::string>> > dicts;
  romanovich::HashTable table;
  for (std::string line; std::getline(std::cin, line);)
  {
    if (!line.empty())
    {
      table.addWord(line);
      table.print(std::cout) << "\n";
    }
  }
}
