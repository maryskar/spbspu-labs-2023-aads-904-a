#include "inputdict.hpp"
#include <istream>
#include <string>
#include "dictionary.hpp"

using dict_t = Dictionary< size_t, std::string >;

void inputDict(std::istream& input, Dictionary< std::string, dict_t >& dict_of_dict)
{
  while (input)
  {
    std::string name = "";
    while (input >> name)
    {
      size_t key;
      std::string value;
      dict_t dict;
      while (input >> key >> value)
      {
        dict.push(key, value);
      }
      dict_of_dict.push(name, dict);
      input.clear();
    }
  }
}
