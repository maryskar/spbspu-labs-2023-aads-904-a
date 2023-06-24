#include <iostream>
#include <fstream>
#include <string>
#include <cstddef>
#include <functional>
#include "dictionary.hpp"
#include "forward-list.hpp"

int main(int argc, char * argv[])
{
  if (argc == 1)
  {
    std::cerr << "no file\n";
    return 1;
  }

  std::ifstream file;
  file.open(argv[1]);
  if (!file.is_open())
  {
    std::cerr << "cannot open file\n";
    return 1;
  }
  using dict_t = turkin::Dictionary< std::size_t, std::string, std::less< std::size_t > >;
  dict_t dict;
  //dict.insert(1, "a");
  dict.insert(2, "a");
  dict.insert(3, "b");
  dict.insert(4, "c");
  dict.insert(2, "a");
  auto a = dict.begin();
  std::string as = a->second;
  std::size_t at = a->first;
  std::cout << "begin key: " << at << "\n";
  std::cout << "begin data: " << as << "\n";
  auto b = dict.end();
  std::string bs = b->second;
  std::size_t bt = b->first;
  std::cout << "end key: " << bt << "\n";
  std::cout << "end data: " << bs << "\n";
  std::cout << "count: " << dict.count(2) << "\n";
  std::cout << "size: " << dict.size() << "\n";
  std::cout << "asd\n";
  /*
  std::string name;
  std::size_t key;
  std::string value;
  while (file)
  {
    file >> name;
    while
    file >> key >> value;
    std::cout <<  << "\n";
  }
*/
  return 0;
}
