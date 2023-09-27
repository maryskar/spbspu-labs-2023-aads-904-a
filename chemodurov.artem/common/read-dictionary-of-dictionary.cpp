#include "read-dictionary-of-dictionary.hpp"
#include <iostream>

using dic_t = chemodurov::Map< int, std::string >;

namespace chemodurov
{
  std::pair< std::string, dic_t > readDicOfIntString(const std::string & data)
  {
    if (data.empty())
    {
      return {"", dic_t{}};
    }
    std::string name;
    dic_t dic;
    size_t read = 0;
    size_t read_from = data.find(' ');
    name = data.substr(read, read_from);
    read = read_from;
    while (read < data.size())
    {
      int key = std::stoi(data.substr(read_from), std::addressof(read));
      read_from += read + 1;
      read = read_from;
      read_from = data.substr(read).find(' ');
      std::string value;
      if (read_from != std::string::npos)
      {
        value = data.substr(read, read_from);
      }
      else
      {
        value = data.substr(read);
        dic.insert({key, value});
        return {name, dic};
      }
      read += read_from;
      read_from = read;
      dic.insert({key, value});
    }
    return {name, dic};
  }
}

chemodurov::Map< std::string, dic_t > chemodurov::readDictionaryOfDictionary(std::istream & in)
{
  Map< std::string, dic_t > res;
  while (in)
  {
    std::string line;
    std::getline(in, line);
    if (!in)
    {
      break;
    }
    std::pair< std::string, dic_t > temp = readDicOfIntString(line);
    if (temp.first.empty())
    {
      continue;
    }
    res.insert(temp);
  }
  return res;
}
