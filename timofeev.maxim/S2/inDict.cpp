#include "inDict.h"
timofeev::dictOfDicts timofeev::inDict(std::istream& in, timofeev::dictOfDicts &dict)
{
  while (in)
  {
    std::string name = "";
    in >> name;
    if (!in || name == "stop")
    {
      break;
    }
    dictionary data;
    std::string val = "";
    int key = 0;
    while (in)
    {
      in >> key >> val;
      if (!in)
      {
        break;
      }
      data.push(key, val);
    }
    in.clear();
    dict.push(name, data);
  }
  return dict;
}

