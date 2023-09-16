#include "commands.hpp"
#include <string>
#include <ostream>
#include <avltree.hpp>

using dict_t = hrushchev::AVLTree< size_t, std::string >;
using main_dict = hrushchev::AVLTree< std::string, dict_t >;

void hrushchev::printDict(std::string name, main_dict& dict_of_dict, std::ostream& out)
{
  try
  {
    dict_t dict = dict_of_dict.at(name);
    if (dict.empty())
    {
      out << "<EMPTY>";
      return;
    }
    out << name;
    for (auto i = dict.begin(); i != dict.end(); i++)
    {
      out << " " << i->first << " " << i->second;
    }
  }
  catch (...)
  {
    throw;
  }
}

void hrushchev::complementDict(std::string name, std::string first, std::string second, main_dict& dict_of_dict)
{
  try
  {
    dict_t temp;
    dict_t first_dict = dict_of_dict.at(first);
    dict_t second_dict = dict_of_dict.at(second);
    for (auto i = first_dict.begin(); i != first_dict.end(); i++)
    {
      try
      {
        second_dict.at(i->first);
      }
      catch (...)
      {
        temp.insert(i->first, i->second);
      }
    }
    for (auto i = second_dict.begin(); i != second_dict.end(); i++)
    {
      try
      {
        first_dict.at(i->first);
      }
      catch (...)
      {
        temp.insert(i->first, i->second);
      }
    }
    dict_of_dict.insert(name, temp);
  }
  catch(...)
  {
    throw;
  }
}

void hrushchev::intersectDict(std::string name, std::string first, std::string second, main_dict& dict_of_dict)
{
  try
  {
    dict_t temp;
    dict_t first_dict = dict_of_dict.at(first);
    dict_t second_dict = dict_of_dict.at(second);
    for (auto i = first_dict.begin(); i != first_dict.end(); i++)
    {
      try
      {
        second_dict.at(i->first);
        temp.insert(i->first, i->second);
      }
      catch (...)
      {
      }
    }
    dict_of_dict.insert(name, temp);
  }
  catch (...)
  {
    throw;
  }
}

void hrushchev::unionDict(std::string name, std::string first, std::string second, main_dict& dict_of_dict)
{
  try
  {
    dict_t temp;
    dict_t first_dict = dict_of_dict.at(first);
    dict_t second_dict = dict_of_dict.at(second);
    for (auto i = second_dict.begin(); i != second_dict.end(); i++)
    {
      temp.insert(i->first, i->second);
    }
    for (auto i = first_dict .begin(); i != first_dict.end(); i++)
    {
      temp.insert(i->first, i->second);
    }
    dict_of_dict.insert(name, temp);
  }
  catch (...)
  {
    throw;
  }
}
