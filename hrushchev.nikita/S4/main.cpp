#include <iostream>
#include <fstream>
#include <string>
#include <list.hpp>
#include <avltree.hpp>
#include <avltreeiterator.hpp>
#include <avltreeconstiterator.hpp>
#include "inputdict.hpp"
#include "commands.hpp"

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

  using dict_t = hrushchev::AVLTree< size_t, std::string >;
  hrushchev::AVLTree< std::string, dict_t > dict_of_dict;
  hrushchev::inputDict(input, dict_of_dict);
  std::string command = "";
  while (std::cin >> command)
  {
    try
    {
      if (command == "print")
      {
        std::string dict_name = "";
        std::cin >> dict_name;
        hrushchev::printDict(dict_name, dict_of_dict, std::cout);
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
          hrushchev::complementDict(res_dict_name, first_dict_name, second_dict_name, dict_of_dict);
        }
        else if (command == "intersect")
        {
          hrushchev::intersectDict(res_dict_name, first_dict_name, second_dict_name, dict_of_dict);
        }
        else if (command == "union")
        {
          hrushchev::unionDict(res_dict_name, first_dict_name, second_dict_name, dict_of_dict);
        }
        else
        {
          std::cout << "<INVALID COMMAND>\n";
        }
      }
    }
    catch (...)
    {
      std::cout << "<INVALID COMMAND>\n";
    }
  }
}
