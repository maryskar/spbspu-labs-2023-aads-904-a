#ifndef SPBSPU_LABS_2023_AADS_904_A_INPUTDICTIONARY_H
#define SPBSPU_LABS_2023_AADS_904_A_INPUTDICTIONARY_H
#include <istream>
namespace dimkashelk
{
  template< typename MainDictType, typename DataDictType >
  void inputDictionary(std::istream &in, MainDictType &dict)
  {
    while (in)
    {
      std::string dict_name;
      in >> dict_name;
      if (!in)
      {
        break;
      }
      DataDictType data;
      int key = 0;
      std::string value;
      while (in)
      {
        in >> key >> value;
        if (!in)
        {
          break;
        }
        data.push(key, value);
      }
      in.clear();
      dict.push(dict_name, data);
    }
  }
}
#endif
