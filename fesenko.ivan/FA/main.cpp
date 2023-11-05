#include <iostream>
#include "commands.h"
int main()
{
  using list_t = fesenko::ForwardList< size_t >;
  using hash_t = fesenko::HashTable< list_t >;
  using data_t = fesenko::HashTable< hash_t >;
  data_t data;
  fesenko::Commands commands;
  std::string cmd = "";
  while (std::cin >> cmd) {
    try {
      commands.make(cmd, data, std::cin, std::cout);
    } catch (const std::exception &e) {
      std::cout << e.what() << "\n";
      return 2;
    }
  }
}
