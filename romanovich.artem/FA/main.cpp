#include <iostream>
#include <cmath>
#include "murmurhash2.h"
#include "hashtable.h"
int main()
{
  HashTable table;
  for (std::string line; std::getline(std::cin, line);)
  {
    if (!line.empty())
    {
      table.addWord(line);
      table.print();
    }
  }
}
