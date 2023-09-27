#include <iostream>
#include <fstream>
#include "AVL.h"
#include "traverseCommands.h"
#include "stringCreator.h"
#include <string>


int main(int argc, char** argv)
{
  using dictionary = dmitriev::AVL< const long long, std::string >;
  using command = dmitriev::StringCreator(*)(const dictionary&, dmitriev::StringCreator);


  if (argc != 3)
  {
    std::cout << "incorrect argc count" << '\n';
    return 1;
  }
  std::ifstream file(argv[2]);
  if (!file.is_open())
  {
    std::cout << "problems with opening file" << '\n';
    return 1;
  }


  int key;
  std::string value;
  dictionary dict;

  while (file >> key >> value)
  {
    dict.insert({key, value});

  }
  if (dict.isEmpty())
  {
    std::cout << "<EMPTY>" << '\n';
    return 0;
  }

  dmitriev::AVL< std::string, command > cmds;
  cmds["ascending"] = dmitriev::doAscending;
  cmds["descending"] = dmitriev::doDescending;
  cmds["breadth"] = dmitriev::doBreadth;

  try
  {
    if (!cmds.isEmpty(cmds.find(argv[1])))
    {
      std::cout << cmds[argv[1]](dict, dmitriev::StringCreator()).result;
      std::cout << "\n";
    }
    else
    {
      std::cerr << "<INVALID COMMAND>\n";
      return 1;
    }
  }
  catch (const std::exception& exception)
  {
    std::cerr << exception.what() << "\n";
    return 1;
  }


  return 0;
}
