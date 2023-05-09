#ifndef DICT_H
#define DICT_H
#include <iostream>
#include <map>
struct Dict
{
  std::string dictName;
  std::map< std::string, int > dict;
};
#endif
