#ifndef SPBSPU_LABS_2023_AADS_904_A_LABLIST1_H
#define SPBSPU_LABS_2023_AADS_904_A_LABLIST1_H
#include <iostream>
#include <fstream>
#include "dictionary.h"
namespace dimkashelk
{
  std::ostream &outCustomErrorMessage(std::ostream &out)
  {
    return out << "<INVALID COMMAND>";
  }
  std::ostream &outEmptyDictionaryMessage(std::ostream &out)
  {
    return out << "<EMPTY>";
  }
  void labList1(std::istream &in, std::ostream &out, int argc, char *argv[])
  {
    using dict_type = dimkashelk::Dictionary< int, std::string, std::less< > >;
    using dict_value_type = std::pair< int, std::string >;
    using container_type = dimkashelk::Dictionary< std::string, dict_type, std::less< > >;
    using container_value_type = std::pair< std::string, dict_type >;
    namespace dsk = dimkashelk;
    if (argc != 2)
    {
      throw std::runtime_error("No filename");
    }
    container_type dict;
    std::ifstream file_in(argv[1]);
    if (!file_in.is_open())
    {
      throw std::runtime_error("File not open");
    }
    while (file_in)
    {
      std::string dict_name;
      file_in >> dict_name;
      if (!file_in)
      {
        break;
      }
      dict_type data;
      int key = 0;
      std::string value;
      while (file_in)
      {
        file_in >> key >> value;
        if (!file_in)
        {
          break;
        }
        std::cout << key << " " << value << "\n";
        data.emplace(dict_value_type(key, value));
      }
      file_in.clear();
      dict.emplace(container_value_type(dict_name, data));
    }
    dimkashelk::Dictionary< std::string, dict_type(*)(const dict_type &, const dict_type &), std::greater< > > commands;
    commands["complement"] = getComplement;
    commands["intersect"] = getIntersection;
    commands["union"] = getUnion;
    while (in)
    {
      std::string command;
      in >> command;
      if (!in)
      {
        break;
      }
      try
      {
        if (command == "print")
        {
          std::string dataset_name;
          in >> dataset_name;
          dict_type d = dict.at(dataset_name);
          if (d.empty())
          {
            outEmptyDictionaryMessage(out) << "\n";
          }
          else
          {
            auto it = d.begin();
            auto end = d.end();
            out << dataset_name << " " << it->first << " " << it->second;
            it++;
            for (; it != end; it++)
            {
              out << " " << it->first << " " << it->second;
            }
            out << "\n";
          }
        }
        else
        {
          auto to_do = commands.at(command);
          std::string new_dataset_name;
          std::string dataset_1;
          std::string dataset_2;
          in >> new_dataset_name >> dataset_1 >> dataset_2;
          dict_type data_1 = dict.at(dataset_1);
          dict_type data_2 = dict.at(dataset_2);
          dict_type new_dict = to_do(data_1, data_2);
          dict.emplace(new_dataset_name, new_dict);
        }
      }
      catch (...)
      {
        outCustomErrorMessage(out) << "\n";
        std::getline(in, command);
      }
    }
  }
}
#endif
