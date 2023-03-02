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
  while (std::cin)
  {
    std::string command = "";
    std::cin >> command;
    if (command == "print")
    {
      std::string dataset_name = "";
      std::cin >> dataset_name;
      for (auto &&begin : list)
      {
        if (begin.first == dataset_name)
        {
          if (begin.second.empty())
          {
            std::cout << "<EMPTY>";
          }
          else
          {
            std::cout << begin.second;
          }
        }
      }
    }
    else if (command == "complement")
    {
      std::string new_dataset_name = "";
      std::string dataset_1 = "";
      std::string dataset_2 = "";
      std::cin >> new_dataset_name >> dataset_1 >> dataset_2;
      dsk::Dictionary< int, std::string, std::less< > > data_1;
      dsk::Dictionary< int, std::string, std::less< > > data_2;
      auto iter = list.begin();
      auto end = list.end();
      while (iter != end)
      {
        if ((*iter).first == dataset_1)
        {
          data_1 = (*iter).second;
        }
        if ((*iter).first == dataset_2)
        {
          data_2 = (*iter).second;
        }
        iter++;
      }
    }
  }
  return 0;
}
