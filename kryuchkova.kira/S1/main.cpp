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
  long long res;
  std::ifstream file;

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
    try
    {
      kryuchkova::Queue< kryuchkova::ExpressionMember > inf = kryuchkova::InfixExp(str);
      kryuchkova::Queue< kryuchkova::ExpressionMember > post = kryuchkova::GetPostfixExp(inf);
      res = kryuchkova::getResult(post);
      std::cout << res << '\n';
      return 0;
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << '\n';
      return 1;
    }
  }
  return 0;
}
