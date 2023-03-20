#ifndef SPBSPU_LABS_2023_AADS_904_A_LABLIST1_H
#define SPBSPU_LABS_2023_AADS_904_A_LABLIST1_H
#include <iostream>
#include <fstream>
#include "inputDictionary.h"
namespace dimkashelk
{
  template< typename MainDictType, typename DataDictType >
  void labList1(std::istream &in, std::ostream &out, int argc, char *argv[])
  {
    namespace dsk = dimkashelk;
    if (argc != 2)
    {
      throw std::runtime_error("No filename");
    }
    MainDictType dict;
    std::ifstream file_in(argv[1]);
    if (!file_in.is_open())
    {
      throw std::runtime_error("File not open");
    }
    dsk::inputDictionary< MainDictType, DataDictType >(file_in, dict);
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
          DataDictType d = dict.get(dataset_name);
          if (d.empty())
          {
            out << "<EMPTY>\n";
          }
          else
          {
            out << dataset_name << " " << d << "\n";
          }
        }
        catch (const std::runtime_error &e)
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
          DataDictType data_1 = dict.get(dataset_1);
          DataDictType data_2 = dict.get(dataset_2);
          DataDictType new_dict;
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
          dict.push(new_dataset_name, new_dict);
        }
        catch (const std::runtime_error &e)
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
