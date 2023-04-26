#ifndef SPBSPU_LABS_2023_AADS_904_A_LABLIST1_H
#define SPBSPU_LABS_2023_AADS_904_A_LABLIST1_H
#include <iostream>
#include <fstream>
#include "dictionary.h"
namespace dimkashelk
{
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
        data.emplace(dict_value_type(key, value));
      }
      file_in.clear();
      dict.emplace(container_value_type(dict_name, data));
    }
    while (in)
    {
      std::string command;
      in >> command;
      if (!in)
      {
        break;
      }
      if (command == "print")
      {
        std::string dataset_name;
        in >> dataset_name;
        if (!in)
        {
          out << "<INVALID COMMAND>\n";
        }
        try
        {
          dict_type d = dict.at(dataset_name);
          if (d.empty())
          {
            out << "<EMPTY>\n";
          }
          else
          {
            out << dataset_name << " " << d << "\n";
          }
        }
        catch (...)
        {
          out << "<INVALID COMMAND>\n";
        }
      }
      else if (command == "complement" || command == "intersect" || command == "union")
      {
        std::string new_dataset_name;
        std::string dataset_1;
        std::string dataset_2;
        in >> new_dataset_name >> dataset_1 >> dataset_2;
        if (!in)
        {
          out << "<INVALID COMMAND>\n";
          continue;
        }
        try
        {
          dict_type data_1 = dict.at(dataset_1);
          dict_type data_2 = dict.at(dataset_2);
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
          dict.emplace(new_dataset_name, new_dict);
        }
        catch (...)
        {
          out << "<INVALID COMMAND>\n";
        }
      }
      else
      {
        out << "<INVALID COMMAND>\n";
        std::getline(in, command);
      }
    }
  }
}
#endif
