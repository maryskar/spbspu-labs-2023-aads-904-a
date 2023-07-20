#include "forwardlist.hpp"
#include "forwardlistiterator.hpp"
#include "forwardlistconstiterator.hpp"
#include "dictionary.hpp"
#include "inputdict.hpp"
#include "commands.hpp"
#include <list.hpp>
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cout << "Error arg\n";
    return 1;
  }
  std::ifstream input(argv[1]);
  if (!input.is_open())
  {
    std::cout << "Error file\n";
    return 1;
  }
  using dict_t = Dictionary< size_t, std::string >;
  Dictionary< std::string, dict_t > dict_of_dict;
  inputDict(input, dict_of_dict);
  std::string command = "";
  while (std::cin >> command)
  {
    if (command == "print")
    {
      std::string dict_name = "";
      std::cin >> dict_name;
      printDict(dict_name, dict_of_dict, std::cout);
      std::cout << "\n";
    }
    else
    {
      std::string res_dict_name = "";
      std::string first_dict_name = "";
      std::string second_dict_name = "";
      std::cin >> res_dict_name >> first_dict_name >> second_dict_name;
      if (command == "complement")
      {
        complementDict(res_dict_name, first_dict_name, second_dict_name, dict_of_dict);
      }
      else if (command == "intersect")
      {
        intersectDict(res_dict_name, first_dict_name, second_dict_name, dict_of_dict);
      }
      else if (command == "union")
      {
        unionDict(res_dict_name, first_dict_name, second_dict_name, dict_of_dict);
      }
    }
  }
}
