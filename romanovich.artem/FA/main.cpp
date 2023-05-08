#include <iostream>
#include "commands.h"
int main()
{
  for (std::string line; std::getline(std::cin, line);)
  {
    if (line.empty())
    {
      continue;
    }
    commandFromString(line);
  }
}