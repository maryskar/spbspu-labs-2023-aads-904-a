#include <iostream>
#include "commands.h"
int main()
{
  std::istream &in = std::cin;
  std::ostream &out = std::cout;
  romanovich::CommandHandler commandHandler(in, out);
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
