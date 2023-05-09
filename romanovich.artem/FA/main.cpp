#include <iostream>
#include <cmath>
#include "commands.h"
int main()
{
  HashTable hashTable(static_cast<size_t>(std::pow(2, 20)));
  for (std::string line; std::getline(std::cin, line);)
  {
    if (!line.empty())
    {
      processCommand(line, hashTable);
    }
  }
}