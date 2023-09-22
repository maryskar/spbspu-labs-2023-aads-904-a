#include "huffman-tree.hpp"

#include <iostream>
#include <string>

int main()
{
  std::cout << "started\n";
  std::string st = "aaabbc";
  HTree tree(st);
  return 0;
}
