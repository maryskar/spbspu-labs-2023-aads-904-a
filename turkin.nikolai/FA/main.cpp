#include "huffman-tree.hpp"
#include "huffman.hpp"

#include <iostream>
#include <string>

int main()
{
  std::string st = "aaaaaabbbcc";
  HTree tree(st);
  std::cout << details::encode(st, tree.get_encoding_map()) << "\n";
  return 0;
}
