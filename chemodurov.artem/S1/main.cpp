#include <iostream>
#include <fstream>
#include "read-infix-expr.hpp"
#include "convert-infix-to-postfix.hpp"
#include "stack.hpp"

int main(int argc, char ** argv)
{
  if (argc != 1 && argc != 2)
  {
    std::cerr << "Error\n";
    return 1;
  }
  std::string line;
  chemodurov::Stack< int > res;
  if (argc == 1)
  {
    do
    {
      std::getline(std::cin, line);
      if (!std::cin)
      {
        break;
      }
      size_t inf_size = 0;
      chemodurov::InfixExpr * inf = chemodurov::readInfixExpr(line, inf_size);
      chemodurov::Queue< chemodurov::InfixExpr > inf_queue;
      try
      {
        for (size_t i = 0; i < inf_size; ++i)
        {
          inf_queue.push(inf[i]);
        }
      }
      catch (...)
      {
        delete[] inf;
        std::cerr << "Error...\n";
        return 1;
      }
      delete[] inf;
      chemodurov::Queue< chemodurov::PostfixExpr > post;
      try
      {
        post = chemodurov::convertInfixToPostfix(inf_queue);
      }
      catch (...)
      {
        std::cerr << "Error...\n";
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
      size_t inf_size = 0;
      chemodurov::InfixExpr * inf = chemodurov::readInfixExpr(line, inf_size);
      chemodurov::Queue< chemodurov::InfixExpr > inf_queue;
      for (size_t i = 0; i < inf_size; ++i)
      {
        inf_queue.push(inf[i]);
      }
      delete[] inf;

    }
    while (input);
  }
  return 0;
}