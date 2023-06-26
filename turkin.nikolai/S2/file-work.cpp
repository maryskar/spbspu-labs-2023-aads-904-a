#include "file-work.hpp"

using dict = turkin::Dictionary< std::size_t, std::string, std::less< std::size_t > >;
using dictArray = turkin::Dictionary< std::string, dict, std::less< std::string > >;

dictArray turkin::genDicts(std::istream & input)
{
  dictArray result;
  while (input)
  {
    std::string name;
    input >> name;
    if (!input)
    {
      break;
    }
    dict data;
    std::size_t key = 0;
    std::string value;
    while (input)
    {
      input >> key >> value;
      if (!input)
      {
        break;
      }
      data.emplace(std::make_pair(key, value));
    }
    input.clear();
    result.emplace(std::make_pair(name, data));
  }
  return result;
}
