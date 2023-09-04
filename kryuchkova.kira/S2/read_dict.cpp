#include "read_dict.h"
#include <iostream>

namespace kryuchkova
{
  Dictionary< std::string, Dictionary< int, std::string, std::less< > >, std::less< > > readDictOfDict(std::istream & in)
  {
    using dictionary = Dictionary< int, std::string, std::less< > >;
    using dict_of_dict = Dictionary< std::string, dictionary, std::less< std::string > >;
    using dictionary_elem = std::pair< int, std::string >;
    using dict_of_dict_elem = std::pair< std::string, dictionary >;
    dict_of_dict container;
    try
    {
      while (in)
      {
        std::string name;
        in >> name;
        if (!in)
        {
          break;
        }
        dictionary dict;
        int key = 0;
        std::string val;
        while (in)
        {
          in >> key >> val;
          if (!in)
          {
            break;
          }
          dict.insert(dictionary_elem(key, val));
        }
        in.clear();
        container.insert(dict_of_dict_elem(name, dict));
        }
    }
    catch(const std::exception & e)
    {
      std::cerr << e.what() << '\n';
    }
  }
}