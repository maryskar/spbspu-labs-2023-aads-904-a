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
    std::string dict_name;
    in >> dict_name;
    if (!in)
    {
      break;
    }
    dict_type dict;
    int key = 0;
    std::string value;
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
    std::string command;
    std::cin >> command;
    if (command == "print")
    {
      std::string dataset_name;
      std::cin >> dataset_name;
      if (!std::cin)
      {
        std::cerr << "<INVALID COMMAND>";
      }
      try
      {
        dict_type dict = search(list, dataset_name);
        if (dict.empty())
        {
          std::cout << "<EMPTY>\n";
        }
        else
        {
          std::cout << dataset_name << " " << dict << "\n";
        }
      }
      catch (const std::runtime_error &e)
      {
        std::cerr << "<INVALID COMMAND>";
      }
    }
    else if (command == "complement" || command == "intersect" || command == "union")
    {
      std::string new_dataset_name;
      std::string dataset_1;
      std::string dataset_2;
      std::cin >> new_dataset_name >> dataset_1 >> dataset_2;
      if (!std::cin)
      {
        std::cerr << "<INVALID COMMAND>";
        continue;
      }
      try
      {
        dict_type data_1 = search(list, dataset_1);
        dict_type data_2 = search(list, dataset_2);
        dict_type new_dict;
        if (command == "complement")
        {
          new_dict = data_1 - data_2;
        }
        else if (command == "intersect")
        {
          new_dict = data_1 & data_2;
        }
        else if (command == "union")
        {
          new_dict = data_1 | data_2;
        }
        list.pushBack(pair_type(new_dataset_name, new_dict));
      }
      catch (const std::runtime_error &e)
      {
        std::cerr << "<INVALID COMMAND>";
      }
    }
  }
  return 0;
}
