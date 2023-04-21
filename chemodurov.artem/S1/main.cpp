#include <iostream>
#include <fstream>
#include "read-infix-expr.hpp"
#include "convert-infix-to-postfix.hpp"
#include "calc-postfix-expr.hpp"
#include "print-stack-long.hpp"

int main(int argc, char ** argv)
{
  if (argc != 1 && argc != 2)
  {
    std::cerr << "Error\n";
    return 1;
  }
  std::string line;
  chemodurov::Stack< long > res;
  std::ifstream file;
  if (argc == 2)
  {
    file.open(argv[1]);
  }
  std::istream & in = (argc == 1) ? std::cin : file;

  do
  {
    std::getline(in, line);
    if (!in)
    {
      break;
    }
    if (line.empty())
    {
      continue;
    }
    chemodurov::Queue< chemodurov::InfixExpr > inf;
    try
    {
      inf = chemodurov::readInfixExpr(line);
    }
    catch (const std::exception & e)
    {
      std::cerr << e.what() << "\n";
      return 1;
    }
    try
    {
      chemodurov::Queue< chemodurov::PostfixExpr > post = chemodurov::convertInfixToPostfix(inf);
      res.push(chemodurov::calcPostfixExpr(post));
    }
    catch (const std::exception & e)
    {
      std::cerr << e.what() << "\n";
      return 1;
    }
  }
  while (in);

  try
  {
    chemodurov::printStackLong(std::cout, res);
  }
  catch (const std::invalid_argument & e)
  {
    std::cout << '\n';
    return 0;
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  std::cout << "\n";
  return 0;
}
