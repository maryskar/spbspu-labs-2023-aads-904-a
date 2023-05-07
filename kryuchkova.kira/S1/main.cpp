#include "queue.h"
#include "stack.h"
#include "get_result.h"
#include "infix_to_postfix.h"
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
  std::ifstream file;
  kryuchkova::Stack< long long > results;

  if (argc == 2)
  {
    file.open(argv[1]);
  }
  std::istream &in = (argc == 1) ? std::cin : file;

  while (in)
  {
    std::getline(in, str);
    if (!in)
    {
      break;
    }
    if (str.empty())
    {
      continue;
    }
    else
    {
      try
      {
        kryuchkova::Queue< kryuchkova::ExpressionMember > inf = kryuchkova::InfixExp(str);
        kryuchkova::Queue< kryuchkova::ExpressionMember > post = kryuchkova::GetPostfixExp(inf);
        results.push(kryuchkova::getResult(post));
      }
      catch (const std::exception &e)
      {
        std::cerr << e.what() << '\n';
        return 1;
      }
    }
  }
  if (results.isEmpty())
  {
    std::cout << '\n';
    return 0;
  }

  std::cout << results.drop();
  while (!results.isEmpty())
  {
    std::cout << ' ' << results.drop();
  }
  std::cout << '\n';
  return 0;
}
