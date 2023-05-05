#include "read-dictionary-of-dictionary.hpp"

using dic_t = chemodurov::Dictionary< int, std::string, std::less< > >;

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
      std::string value = data.substr(read, read_from - read);
      read = read_from;
      dic.insert({key, value});
    }
    return {name, dic};
  }
}

chemodurov::Dictionary< std::string, dic_t, std::less<> > chemodurov::readDictionaryOfDictionary(std::istream & in)
{
  Dictionary< std::string, dic_t, std::less<> > res;
  while (in)
  {
    std::string line;
    std::getline(in, line);
    std::pair< std::string, dic_t > temp = readDicOfIntString(line);
    if (temp.first.empty())
    {
      continue;
    }
    res.insert(temp);
  }
  return res;
}
