#include "commands.hpp"
#include <string>
#include <ostream>
#include "dictionary.hpp"

using dict_t = Dictionary< size_t, std::string >;

void printDict(std::string name, Dictionary< std::string, dict_t >& dict_of_dict, std::ostream& out)
{
  out << name << " ";
  dict_t dict = dict_of_dict.get(name);
  if (dict.empty())
  {
    out << "<EMPTY>";
    return;
  }
  for (auto i = dict.begin(); i != dict.end(); i++)
  {
    out << i->first << " " << i->second << " ";
  }
}

void complementDict(std::string name, std::string first, std::string second, Dictionary< std::string, dict_t >& dict_of_dict)
{
  dict_t temp;
  dict_t first_dict = dict_of_dict.get(first);
  dict_t second_dict = dict_of_dict.get(second);
  for (auto i = first_dict.begin(); i != first_dict.end(); i++)
  {
    try
    {
      second_dict.at(i->first);
    }
    catch (...)
    {
      temp.insert(*i);
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
      temp.insert(*i);
    }
  }
  dict_of_dict.push(name, temp);
}

void intersectDict(std::string name, std::string first, std::string second, Dictionary< std::string, dict_t >& dict_of_dict)
{
  dict_t temp;
  dict_t first_dict = dict_of_dict.get(first);
  dict_t second_dict = dict_of_dict.get(second);
  for (auto i = first_dict.begin(); i != first_dict.end(); i++)
  {
    try
    {
      second_dict.at(i->first);
      temp.insert(*i);
    }
    catch (...)
    {
    }
  }
  dict_of_dict.push(name, temp);
}

void unionDict(std::string name, std::string first, std::string second, Dictionary< std::string, dict_t >& dict_of_dict)
{
  dict_t temp;
  dict_t first_dict = dict_of_dict.get(first);
  dict_t second_dict = dict_of_dict.get(second);
  for (auto i = second_dict.begin(); i != second_dict.end(); i++)
  {
    temp.insert(*i);
  }
  for (auto i = first_dict .begin(); i != first_dict.end(); i++)
  {
    temp.insert(*i);
  }
  dict_of_dict.push(name, temp);
}
