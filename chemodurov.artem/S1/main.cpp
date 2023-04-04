#include <iostream>
#include <fstream>
#include "read-infix-expr.hpp"
#include "convert-infix-to-postfix.hpp"
#include "calc-postfix-expr.hpp"
#include "print-stack-int.hpp"

int main(int argc, char ** argv)
{
  if (argc != 1 && argc != 2)
  {
    std::cerr << "Error\n";
    return 1;
  }
  std::string line;
  chemodurov::Stack< long > res;
  if (argc == 1)
  {
    do
    {
      std::getline(std::cin, line);
      if (!std::cin)
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
    while (std::cin);
  }
  else
  {
    std::ifstream input(argv[1]);
    if (!input.is_open())
    {
      std::cerr << "Error while reading\n";
      return 1;
    }

    do
    {
      std::getline(input, line);
      if (!input)
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
    while (input);
  }
  try
  {
    chemodurov::printStackInt(std::cout, res);
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
