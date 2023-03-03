#include <iostream>
#include <functional>
#include <fstream>
#include "dictionary.h"
#include "forwardlist.h"
using pair_type = std::pair< std::string, dimkashelk::Dictionary< int, std::string, std::less< > > >;
using dict_type = dimkashelk::Dictionary< int, std::string, std::less< > >;
using list_type = dimkashelk::ForwardList< pair_type >;
dict_type search(const list_type &list, const std::string& name)
{
  for (auto &&iter: list)
  {
    if (iter.first == name)
    {
      return iter.second;
    }
  }
  throw std::runtime_error("Nothing to return");
}
int main(int argc, char *argv[])
{
  namespace dsk = dimkashelk;
  if (argc != 2)
  {
    std::cerr << "No filename";
    return 1;
  }
  list_type list;
  std::ifstream in(argv[1]);
  if (!in.is_open())
  {
    std::cerr << "File not open";
    return 1;
  }
  while (in)
  {
    std::string dict_name = "";
    in >> dict_name;
    if (!in)
    {
      break;
    }
    dict_type dict;
    int key = 0;
    std::string value = "";
    while (in)
    {
      in >> key >> value;
      if (!in)
      {
        break;
      }
      dict.push(key, value);
    }
    in.clear();
    pair_type pair(dict_name, dict);
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
      std::cout << "\n";
    }
    else if (command == "complement")
    {
      std::string new_dataset_name = "";
      std::string dataset_1 = "";
      std::string dataset_2 = "";
      std::cin >> new_dataset_name >> dataset_1 >> dataset_2;
      dict_type data_1;
      dict_type data_2;
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
      auto new_dict = data_1 - data_2;
      list.pushBack(pair_type(new_dataset_name, new_dict));
    }
    else if (command == "intersect")
    {

    }
  }
  return 0;
}
