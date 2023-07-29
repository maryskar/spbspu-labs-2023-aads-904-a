#ifndef FUNCS_FOR_COMMANDS_H
#define FUNCS_FOR_COMMANDS_H

#include <iostream>
#include <string>
#include <functional>
#include "dictionary.h"

namespace tarasenko
{
  template< class Key, class Value, class Compare >
  Dictionary< Key, Value, Compare > complement(const Dictionary< Key, Value, Compare >& lhs,
     const Dictionary< Key, Value, Compare >& rhs)
  {
    auto result = lhs;
    if (!lhs.isEmpty() && !rhs.isEmpty())
    {
      auto iter_lhs = lhs.cbegin();
      for (; iter_lhs != lhs.cend(); iter_lhs++)
      {
        if (rhs.find((*iter_lhs).first) != rhs.cend())
        {
          result.remove((*iter_lhs).first);
        }
      }
    }
    return result;
  }

  template< class Key, class Value, class Compare >
  Dictionary< Key, Value, Compare > intersect(const Dictionary< Key, Value, Compare >& lhs,
     const Dictionary< Key, Value, Compare >& rhs)
  {
    if (rhs.isEmpty())
    {
      return rhs;
    }
    Dictionary< Key, Value, Compare > result;
    if (!lhs.isEmpty())
    {
      auto iter_lhs = lhs.cbegin();
      for (; iter_lhs != lhs.cend(); iter_lhs++)
      {
        if (rhs.find((*iter_lhs).first) != rhs.cend())
        {
          result.push((*iter_lhs).first, (*iter_lhs).second);
        }
      }
    }
    return result;
  }

  template< class Key, class Value, class Compare >
  Dictionary< Key, Value, Compare > unionWith(const Dictionary< Key, Value, Compare >& lhs,
     const Dictionary< Key, Value, Compare >& rhs)
  {
    if (lhs.isEmpty())
    {
      return rhs;
    }
    auto result = lhs;
    if (!rhs.isEmpty())
    {
      auto iter_rhs = rhs.cbegin();
      for (; iter_rhs != rhs.cend(); iter_rhs++)
      {
        if (lhs.find((*iter_rhs).first) == lhs.cend())
        {
          result.push((*iter_rhs).first, (*iter_rhs).second);
        }
      }
    }
    return result;
  }

  template< class Key, class Value, class Compare >
  std::ostream& print(std::ostream& output, const std::string& name_of_dict,
     const Dictionary< Key, Value, Compare >& dict)
  {
    if (!dict.isEmpty())
    {
      output << name_of_dict << " ";
      auto iter = dict.cbegin();
      output << iter->first << " " << iter->second;
      ++iter;
      while (iter != dict.cend())
      {
        output << " " << iter->first << " " << iter->second;
        ++iter;
      }
    }
    return output;
  }

  template< class Key, class Value, class Compare >
  std::istream& operator>>(std::istream& input, Dictionary< Key, Value, Compare >& dict)
  {
    Key key;
    Value value;
    while (input >> key >> value)
    {
      dict.push(key, value);
    }
    return input;
  }

  template< class Key, class Value, class Compare >
  void add(std::istream& input, Dictionary< Key, Value, Compare >& dict)
  {
    while (input)
    {
      char begin = ' ';
      input >> begin;
      if (begin != '(')
      {
        input.putback(begin);
        break;
      }
      char end = ' ';
      while (input >> end)
      {
        if (end == ')')
        {
          break;
        }
        else
        {
          input.putback(end);
        }
        Key key;
        Value value;
        input >> key >> value;
        dict.push(key, value);
        input.clear();
      }
    }
  }

  template< class Key, class Value, class Compare >
  void deleteDicts(std::istream& input, Dictionary< std::string,
     Dictionary< Key, Value, Compare >, std::greater<> >& dict_of_dict)
  {
    std::string line;
    std::getline(input, line);
    std::string key = "";
    for (size_t i = 0; i < line.size(); i++)
    {
      if (line[i] == ' ')
      {
        dict_of_dict.remove(key);
      }
      else
      {
        key += line[i];
      }
    }
    if (key != "")
    {
      dict_of_dict.remove(key);
      return;
    }
    throw std::invalid_argument("Incorrect key");
  }

//  write <dataset-1><dataset-2> ... <namefile> (записать указанные словари в файл на отдельной строке имя словаря ключ значение ключ значение ...)

//  resort <greater/less> (изменить порядок ключей(сортировку) в словарях)
//  second 1 name 2 sec 4 mouse
//
//    resort less
//    print second
//  4 mouse 2 sec 1 name

//    put <key-1-1> <value-1-1><dataset-1><dataset-2> ... (записать новый элемент в указанные словари, если ключ уже существует, то значение обновляется)
//  print_if <key-1-1> (выводит имена словарей, в которых есть заданный ключ)
//  swap <dataset-1> <dataset-2> (меняет данные двух словарей)
//
//  first 1 base 2 market 3 cats
//    second 1 name 2 sec 4 mouse
//
//    swap first second
//  print first
//  1 name 2 sec 4 mouse
//    print second
//  1 base 2 market 3 cats
//    copy <dataset> <newdataset> (создает копию указанного словаря с новым именем)
//  second 1 name 2 sec 4 mouse
//
//    copy second new
//  print new
//
//  1 name 2 sec 4 mouse
//    update <dataset-1> <dataset-2> (обновляет значения первого словаря значениями из второго словаря по совпадающим ключам)
//  first 1 base 2 market 3 cats
//    second 1 name 2 sec 4 mouse
//
//    update first second
//  print first
//
//  1 name 2 sec 3 cats
//    merge <dataset-1> <dataset-2> (добавляет ключи из второго словаря в первый. Если ключи дублируются, в качестве значения выбираются данные из правого операнда)
//
//  merge first second
//    print first
//  1 name 2 sec 3 cats 4 mouse
//    random <newdataset> <size><dataset-1><dataset-2>...(создает, новый словарь с заданный количеством случайным слов из указанных словарей)
//
//  random four 4
//  print four
//  1 dog 2 tree 3 fish 4 frogs
//    subset <dataset-1> <dataset-2> ( проверяет, является ли первый словарь подмножеством второго)
//  subset second first
//  true
}
#endif
