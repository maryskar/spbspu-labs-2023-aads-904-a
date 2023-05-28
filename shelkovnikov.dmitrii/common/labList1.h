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
  template< typename K, typename V, typename C >
  using tree = dimkashelk::TwoThreeTree< K, V, C >;
  template< typename K, typename V, typename C >
  tree< K, V, C > getIntersection(const tree< K, V, C > &first, const tree< K, V, C > &second)
  {
    tree< K, V, C > result;
    for (auto it_first = second.cbegin(); it_first != second.cend(); it_first++)
    {
      auto res = second.cend();
      for (auto i = first.cbegin(); i != first.cend(); i++)
      {
        if (details::isEqual< K, C >(it_first->first, i->first))
        {
          res = i;
          break;
        }
      }
      if (res != second.cend())
      {
        result[res->first] = res->second;
      }
    }
    return result;
  }
  template< typename K, typename V, typename C >
  tree< K, V, C > getComplement(const tree< K, V, C > &first, const tree< K, V, C > &second)
  {
    tree< K, V, C > new_dict;
    if (std::addressof(first) == std::addressof(second))
    {
      return new_dict;
    }
    auto iter_first = first.cbegin();
    auto iter_first_end = first.cend();
    auto iter_second = second.cbegin();
    auto iter_second_end = second.cend();
    C comp = C{};
    while (iter_first != iter_first_end && iter_second != iter_second_end)
    {
      while (iter_second != iter_second_end && comp((*iter_second).first, (*iter_first).first))
      {
        iter_second++;
      }
      if (iter_second == iter_second_end)
      {
        break;
      }
      if (details::isNotEqual< K, C >(iter_first->first, iter_second->first))
      {
        new_dict[iter_first->first] = iter_first->second;
      }
      iter_first++;
    }
    while (iter_first != iter_first_end)
    {
      new_dict[iter_first->first] = iter_first->second;
      iter_first++;
    }
    return new_dict;
  }
  template< typename K, typename V, typename C >
  tree< K, V, C > getUnion(const tree< K, V, C > &first, const tree< K, V, C > &second)
  {
    tree< K, V, C > new_dict;
    auto iter_second = second.cbegin();
    auto iter_second_end = second.cend();
    while (iter_second != iter_second_end)
    {
      new_dict[iter_second->first] = iter_second->second;
      iter_second++;
    }
    auto iter_first = first.cbegin();
    auto iter_first_end = first.cend();
    while (iter_first != iter_first_end)
    {
      new_dict[iter_first->first] = iter_first->second;
      iter_first++;
    }
    return new_dict;
  }
  template< typename K, typename V, typename C >
  std::ostream &operator<<(std::ostream &out, tree< K, V, C > &dict)
  {
    if (dict.empty())
    {
      return out << "<EMPTY>";
    }
    auto it = dict.cbegin();
    auto end = dict.cend();
    out << it->first << " " << it->second;
    it++;
    for (; it != end; it++) {
      out << " " << it->first << " " << it->second;
    }
    return out;
  }
  std::ostream &outEmptyDictionaryMessage(std::ostream &out)
  {
    return out << "<EMPTY>";
  }
  void labList1(std::istream &in, std::ostream &out, int argc, char *argv[])
  {
    using dict_type = dimkashelk::TwoThreeTree< int, std::string, std::less< > >;
    using container_type = dimkashelk::TwoThreeTree< std::string, dict_type, std::less< > >;
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
    commands.insert("complement", getComplement);
    commands.insert("intersect", getIntersection);
    commands.insert("union", getUnion);
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
