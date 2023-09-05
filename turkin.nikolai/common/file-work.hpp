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
      std::size_t key = 0;
      std::string value;
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
}

#endif
