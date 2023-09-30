#include "read_dicts_in_dict.h"

void tarasenko::readDictsInDict(std::istream& input, Dictionary< std::string, dict_t, std::greater<> >& dict_of_dict)
{
  while (input)
  {
    std::string name_of_dict = "";
    while (input >> name_of_dict)
    {
      size_t key;
      std::string value;
      dict_t dict;
      while (input >> key >> value)
      {
        dict.push(key, value);
      }
      dict_of_dict.push(name_of_dict, dict);
      input.clear();
    }
  }
}
