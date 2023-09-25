#ifndef GENDICTOFDICTS_H
#define GENDICTOFDICTS_H
#include <istream>
#include <utility>
namespace fesenko
{
  template< typename StorageOfStorages, typename Storage >
  StorageOfStorages genDictOfDicts(std::istream &in)
  {
    StorageOfStorages result;
    while (in) {
      std::string name;
      in >> name;
      if (!in) {
        break;
      }
      Storage data;
      int key = 0;
      std::string value = "";
      while (in) {
        in >> key >> value;
        if (!in) {
          break;
        }
        data.insert(std::make_pair(key, value));
      }
      in.clear();
      result.insert(std::make_pair(name, data));
    }
    return result;
  }
}
#endif
