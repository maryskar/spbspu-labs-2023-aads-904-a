#include <iostream>
#include <functional>
#include <fstream>
#include "dictionary.h"
using dict_type = dimkashelk::Dictionary< int, std::string, std::greater< > >;
using container_type = dimkashelk::Dictionary< std::string, dict_type, std::greater< > >;
int main(int argc, char *argv[])
{
  namespace dsk = dimkashelk;
  if (argc != 2)
  {
    std::cerr << "No filename";
    return 1;
  }
  container_type list;
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
    list.push(dict_name, dict);
  }
  while (std::cin)
  {
    std::string command;
    std::cin >> command;
    if (!std::cin)
    {
      break;
    }
    if (command == "print")
    {
      std::string dataset_name;
      std::cin >> dataset_name;
      if (!std::cin)
      {
        std::cerr << "<INVALID COMMAND>\n";
      }
      try
      {
        dict_type dict = list.get(dataset_name);
        std::cout << dataset_name << " " << dict << "\n";
      }
      catch (const std::runtime_error &e)
      {
        std::cerr << "<INVALID COMMAND>\n";
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
        std::cerr << "<INVALID COMMAND>\n";
        continue;
      }
      try
      {
        dict_type data_1 = list.get(dataset_1);
        dict_type data_2 = list.get(dataset_2);
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
        list.push(new_dataset_name, new_dict);
      }
      catch (const std::runtime_error &e)
      {
        std::cerr << "<INVALID COMMAND>\n";
      }
    }
    else
    {
      std::cout << "<INVALID COMMAND>\n";
      std::getline(std::cin, command);
    }
  }
  return 0;
}
