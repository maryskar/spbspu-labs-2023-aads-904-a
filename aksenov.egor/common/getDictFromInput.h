#ifndef GETDICTFROMINPUT_H
#define GETDICTFROMINPUT_H
#include <istream>
#include <utility>

namespace aksenov
{
  template< typename DictOfDicts, typename Dict >
  DictOfDicts getDictFromInput(std::istream &in)
  {
    DictOfDicts res;
    while (in)
    {
      std::string name = "";
      in >> name;
      if (!in)
      {
        break;
      }
      Dict data;
      std::string val = "";
      int key = 0;
      while (in)
      {
        in >> key >> val;
        if (!in)
        {
          break;
        }
        data.insert(std::make_pair(key, val));
      }
      in.clear();
      res.insert(std::make_pair(name, data));
    }
    return res;
  }
}
#endif
