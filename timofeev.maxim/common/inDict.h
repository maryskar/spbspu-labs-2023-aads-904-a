#ifndef S2_INDICT_H
#define S2_INDICT_H
#include <istream>
#include <limits>
#include "Dictionary.h"
namespace timofeev
{
  template< typename A, typename  B >
  A inDict(std::istream& in, A &dict)
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
      B dict_t;
      while (in)
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
}
#endif
