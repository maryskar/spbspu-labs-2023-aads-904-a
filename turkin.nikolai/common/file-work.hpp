#ifndef FILE_WORK_HPP
#define FILE_WORK_HPP

#include <fstream>
#include <string>
#include <functional>
#include <cstddef>

namespace turkin
{
  template< class StorageA, class StorageC >
  StorageA genDicts(std::istream & input)
  {
    StorageA result;
    while (input)
    {
      std::string name;
      input >> name;
      if (!input)
      {
        break;
      }
      StorageC data;
      long long key = 0;
      std::string value = "";
      while (input)
      {
        input >> key >> value;
        if (!input)
        {
          break;
        }
        data.insert(key, value);
      }
      input.clear();
      result.insert(name, data);
    }
    return result;
  }

  template< class Storage >
  Storage genDict(std::istream & input)
  {
    Storage result;
    long long key = 0;
    std::string value = "";
    while (input)
    {
      input >> key >> value;
      if (!input)
      {
        break;
      }
      result.insert(key, value);
    }
    input.clear();
    return result;
  }
}

#endif
