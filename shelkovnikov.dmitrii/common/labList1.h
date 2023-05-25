#ifndef SPBSPU_LABS_2023_AADS_904_A_LABLIST1_H
#define SPBSPU_LABS_2023_AADS_904_A_LABLIST1_H
#include <iostream>
#include <fstream>
#include "twothreetree/twoThreeTree.h"
namespace dimkashelk
{
  std::ostream &outCustomErrorMessage(std::ostream &out)
  {
    return out << "<INVALID COMMAND>";
  }
  void labList1(std::istream &in, std::ostream &out, int argc, char *argv[])
  {
    using dict_type = dimkashelk::TwoThreeTree< int, std::string, std::less< > >;
    using dict_value_type = std::pair< int, std::string >;
    using container_type = dimkashelk::TwoThreeTree< std::string, dict_type, std::less< > >;
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
        data.insert(key, value);
      }
      file_in.clear();
      dict.insert(dict_name, data);
    }
    dimkashelk::TwoThreeTree< std::string, dict_type(*)(const dict_type &, const dict_type &), std::greater< > > commands;
    //commands.insert("complement", getComplement);
    //commands.insert("intersect", getIntersection);
    //commands.insert("union", getUnion);
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
          dict_type d = dict.get(dataset_name);
          if (d.empty())
          {
            out << "<EMPTY>\n";
          }
          else
          {
            //out << dataset_name << " " << d << "\n";
          }
        }
        else
        {
          auto to_do = commands.get(command);
          std::string new_dataset_name;
          std::string dataset_1;
          std::string dataset_2;
          in >> new_dataset_name >> dataset_1 >> dataset_2;
          dict_type data_1 = dict.get(dataset_1);
          dict_type data_2 = dict.get(dataset_2);
          dict_type new_dict = to_do(data_1, data_2);
          dict.insert(new_dataset_name, new_dict);
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
