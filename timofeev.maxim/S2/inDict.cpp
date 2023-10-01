#include "inDict.h"
void timofeev::inDict(std::istream& in, timofeev::dictOfDicts &dict)
{
  while (in)
  {
    std::string name = "";
    in >> name;
   /* if (name == "stop")
    {
      break;
    }*/
    size_t key;
    std::string value;
    dictionary dict_t;
    while (in >> key >> value)
    {
      if (!in)
      {
        break;
      }
      dict_t.push(key, value);
    }
    in.clear();
    dict.push(name, dict_t);
  }
}
