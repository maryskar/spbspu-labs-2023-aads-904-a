#include <iostream>
#include <fstream>
#include <string>
#include <cstddef>
#include <functional>
#include <utility>
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
  //dict.emplace(std::make_pair(12, "one"));
  //dict.insert(12, "a");
  dict.insert(2, "a");
  dict.insert(32, "b");
  dict.insert(4, "c");
  //dict.insert(8, "a");
  std::cout << "erase: " << dict.erase(4) << "\n";
  for (auto a = dict.begin(); a != dict.end(); a++)
  {
    std::string as = a->second;
    std::size_t at = a->first;
    std::cout << "key: " << at << "\t";
    std::cout << "data: " << as << "\n";
  }
  std::cout << "count: " << dict.count(2) << "\n";
  std::cout << "size: " << dict.size() << "\n";
  std::cout << "__END__\n";
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
