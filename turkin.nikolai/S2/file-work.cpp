#include "file-work.hpp"

using dict_t = turkin::Dictionary< std::size_t, std::string, std::less< std::size_t > >;
using dict_a = turkin::Dictionary< std::string, dict_t, std::less< std::string > >;

dict_a turkin::genDicts(std::istream & input)
{
  dict_a result;
  while (input)
  {
    std::string name;
    input >> name;
    if (!input)
    {
      break;
    }
    dict_t data;
    std::size_t key = 0;
    std::string value;
    while (input)
    {
      input >> key >> value;
      if (!input)
      {
        break;
      }
      data.emplace(key, value);
    }
    input.clear();
    result.emplace(name, data);
  }
  return result;
}
