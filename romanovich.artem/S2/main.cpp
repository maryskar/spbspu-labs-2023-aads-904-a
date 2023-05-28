#include <iostream>
#include <string>
#include "dict.h"
int main(int argc, char **argv)
{
  if (argc % 2 == 1)
  {
    std::cerr << "Not appropriate parameters number.\n";
    return 1;
  }
  std::string dict = argv[1];
  Dictionary< int, std::string > dictionary{};
  for (size_t i = 2; i < argc; i += 2)
  {
    int key = std::stoi(argv[i]);
    std::string value = argv[i + 1];
    //dictionary.insert(key, value);
    ///std::cout  <<  key << " " <<   value << "\n";
  }
}
