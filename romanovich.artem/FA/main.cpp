#include <iostream>
#include "commands.h"
int main()
{
  std::istream &in = std::cin;
  romanovich::CommandHandler commandHandler(in);
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
