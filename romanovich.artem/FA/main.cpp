#include <iostream>
#include "murmurhash2.h"
int main()
{
  std::string input = "Hello world";
  std::cout << generateMurmurHash2(std::addressof(input), 0x5bd1e995, 24);
}