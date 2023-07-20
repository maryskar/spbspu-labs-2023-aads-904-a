#include "forwardlist.hpp"
#include "forwardlistiterator.hpp"
#include "forwardlistconstiterator.hpp"
#include "dictionary.hpp"
#include "inputdict.hpp"
#include "commands.hpp"
#include <list.hpp>
#include <iostream>
#include <string>

int main()
{
  Dictionary< int, std::string > dict;
  Dictionary< std::string, dict_t > dict_of_dict;
  inputDict(std::cin, dict_of_dict);
  complementDict("third", "first", "second", dict_of_dict);
  std::cout << "\n";
  for (auto i = dict_of_dict.begin(); i != dict_of_dict.end(); i++)
  {
    std::cout << (*i).first << " ";
    for (auto j = (*i).second.begin(); j != (*i).second.end(); j++)
    {
      std::cout << (*j).first << " " << (*j).second << " ";
    }
    std::cout << "\n";
  }

}
