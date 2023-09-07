#include "read_dict.h"
#include <iostream>

namespace kryuchkova
{
  Dictionary< std::string, Dictionary< int, std::string, std::less< > >, std::less< std:: string> > readDictOfDict(std::istream & in)
  {
    using dictionary = Dictionary< int, std::string, std::less< > >;
    using dict_of_dict = Dictionary< std::string, dictionary, std::less< std::string > >;
    using dictionary_elem = std::pair< int, std::string >;
    using dict_of_dict_elem = std::pair< std::string, dictionary >;
    dict_of_dict container;
    while (in)
    {
      std::string name;
      in >> name;
      if (!in)
      {
        throw;
      }
      dictionary dict;
      int key = 0;
      std::string val;
      while (in)
      {
        in >> key >> val;
        if (!in)
        {
          throw;
        }
        dict.insert(dictionary_elem(key, val));
      }
      in.clear();
      container.insert(dict_of_dict_elem(name, dict));
    }
    return container;
  }
}