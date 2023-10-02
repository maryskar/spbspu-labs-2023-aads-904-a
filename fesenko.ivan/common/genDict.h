#ifndef GENDICT_H
#define GENDICT_H
#include <istream>
#include <utility>
namespace fesenko
{
  template< typename Storage >
  Storage genDict(std::istream &in)
  {
    Storage result;
    long long key = 0;
    std::string value = "";
    while (in) {
      in >> key >> value;
      if (!in) {
        break;
      }
      result.insert(std::make_pair(key, value));
    }
    in.clear();
    return result;
  }
}
#endif
