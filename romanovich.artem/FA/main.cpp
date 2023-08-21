#include <iostream>
#include "murmurhash2.h"
#include "hashtable.h"
#include "commands.h"
int main()
{
  romanovich::HashTable table;
  std::istream &in = std::cin;
  auto commandHandler = romanovich::CommandHandler(&table, in);
  while (in)
  {
    std::string command;
    std::cin >> command;
    if (!in)
    {
      break;
    }
    commandHandler(command);
  }
}
