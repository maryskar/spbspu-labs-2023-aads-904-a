#include "queue.h"
#include "stack.h"
#include "node.h"
#include "infix_exp.h"
#include "part_of_exp.h"
#include <iostream>
#include <fstream>
#include <sstream>


int main(int argc, char *argv[])
{
  if (argc != 1 && argc != 2)
  {
    std::cerr  << "Not correct number of arguments for program\n";
    return 1;
  }

  std::string str;

  if (argc == 2)
  {
    std::ifstream file(argv[1]);
    if (!file)
    {
      std::cerr << "Error with opening file";
      return 1;
    }
    while (!file.eof())
    {
      std::getline(file, str);
      if (str.empty())
      {
        continue;
      }
      try
      {
        kryuchkova::Queue< kryuchkova::ExpressionMember > inf = kryuchkova::InfixExp(str);
      }
      catch(const std::exception& e)
      {
        std::cerr << e.what() << '\n';
      }
    }
  }

  else
  {
    while (std::cin)
    {
      std::getline(std::cin, str);
      if (!std::cin)
      {
        break;
      }
      if (str.empty())
      {
        continue;
      }
      try
      {

      }
      catch(const std::exception& e)
      {
        std::cerr << e.what() << '\n';
      }
      std::cout << 'a' << '\n';
    }
  }
  return 0;
}
