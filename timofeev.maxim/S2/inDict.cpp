#include "inDict.h"
timofeev::dictOfDicts timofeev::inDict(std::istream& in, timofeev::dictOfDicts &dict)
{
  while (!in.eof())
  {
    std::string name = "";
    in >> name;
    if (in.fail())
    {
      in.clear();
      break;
    }
    size_t key = 0;
    std::string value = "";
    dictionary dict_t;
    while (!in.eof())
    {
      in >> key >> value;
      if (in.fail())
      {
        in.clear();
        break;
      }
      dict_t.push(key, value);
    }
    if (in.eof())
    {
      in.clear();
    }
    dict.push(name, dict_t);
  }
  return dict;
}

