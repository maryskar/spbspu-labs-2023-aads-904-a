#include <iostream>
#include <fstream>
#include "infix-expression.hpp"
#include "read-infix-expr.hpp"

int main(int argc, char ** argv)
{
  if (argc != 1 && argc != 2)
  {
    std::cerr << "Error\n";
    return 1;
  }
  std::string line;
  if (argc == 1)
  {
    size_t inf_size = 0;
    chemodurov::InfixExpr * inf = chemodurov::readInfixExpr(std::cin, inf_size);
    //
    delete [] inf;
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
      size_t inf_size = 0;
      chemodurov::InfixExpr * inf = chemodurov::readInfixExpr(input, inf_size);
      //
      delete [] inf;
    }
    while (input);
  }
  return 0;
}