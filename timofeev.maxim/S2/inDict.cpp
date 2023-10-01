#include "inDict.h"
void timofeev::inDict(std::istream& in, timofeev::dictOfDicts &dict)
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
    size_t key;
    std::string value;
    dictionary dict_t;
    while (in >> key >> value)
    {
      dict_t.push(key, value);
    }
    if (in.eof())
    {
      in.clear();
    }
    dict.push(name, dict_t);
  }
}

