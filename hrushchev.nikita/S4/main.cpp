#include <iostream>
#include <fstream>
#include <string>
#include <list.hpp>
#include "avltree.hpp"
#include "workwithdict.hpp"
#include "inputdict.hpp"

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
  hrushchev::Commands dict_wiht_cmd;
  dict_wiht_cmd.runCommand(std::cin, std::cout, dict_of_dict);
}
