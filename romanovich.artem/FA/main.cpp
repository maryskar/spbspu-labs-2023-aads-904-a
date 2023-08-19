#include <iostream>
#include <cmath>
#include "murmurhash2.h"
int main()
{
  for (std::string line; std::getline(std::cin, line);)
  {
    if (!line.empty())
    {
      std::cout << romanovich::generateMurmurHash2(line);
    }
  }
}
