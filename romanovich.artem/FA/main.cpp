#include <iostream>
#include <cmath>
#include "murmurhash2.h"
#include "hashtable.h"
int main()
{
  for (std::string line; std::getline(std::cin, line);)
  {
    HashTable table;
    if (!line.empty())
    {
      table.addWord(line);
      table.print();
    }
  }
}
