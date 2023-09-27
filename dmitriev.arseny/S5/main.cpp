#include <iostream>
#include <fstream>
#include <string>
#include <AVL.h>
#include <outputOfSpecialMessages.h>
#include "stringCreator.h"
#include "traverseCommands.h"


int main(int argc, char** argv)
{
  using dictionary = dmitriev::AVL< const long long, std::string >;
  using comands = dmitriev::AVL< std::string, dmitriev::StringCreator(*)(dictionary&, dmitriev::StringCreator) >;

  if (argc != 3)
  {
    std::cout << "incorrect argc count" << '\n';
    return 1;
  }
  std::ifstream file (argv[2]);
  if (!file.is_open())
  {
    std::cout << "problems with opening file" << '\n';
    return 1;
  }


  size_t key;
  std::string value;
  dictionary dict;

  while (file >> key >> value)
  {
    dict.insert({key, value});
  }

  if (dict.isEmpty())
  {
    dmitriev::outOfEmptyDataMsg() << '\n';
    return 0;
  }

  comands cmds;
  cmds["ascending"] = dmitriev::doAscending;
  cmds["descending"] = dmitriev::doDescending;
  cmds["breadth"] = dmitriev::doBreadth;





  return 0;
}
