#include <iostream>
#include <functional>
#include <fstream>
#include "dictionary.h"
#include "forwardlist.h"
int main(int argc, char *argv[])
{
  namespace dsk = dimkashelk;
  if (argc != 2)
  {
    std::cerr << "No filename";
    return 1;
  }
  using data_type = std::pair< std::string, dsk::Dictionary< int, std::string, std::less< > > >;
  dsk::ForwardList< data_type > list;
  //std::ifstream in(argv[1]);
  //if (!in.is_open())
  //{
  //  std::cerr << "File not open";
  //  return 1;
  //}
  while (std::cin)
  {
    std::string dict_name = "";
    std::cin >> dict_name;
    if (!std::cin)
    {
      break;
    }
    dsk::Dictionary< int, std::string, std::less< > > dict;
    int key = 0;
    std::string value = "";
    while (std::cin)
    {
      std::cin >> key >> value;
      if (!std::cin)
      {
        break;
      }
      dict.push(key, value);
    }
    std::cin.clear();
    data_type pair(dict_name, dict);
    list.pushBack(pair);
  }
  auto iterator = list.begin();
  std::cout << (*iterator).first << " " <<  (*iterator).second << "\n";
  iterator++;
  std::cout << (*iterator).first << " " <<  (*iterator).second;
  return 0;
}
