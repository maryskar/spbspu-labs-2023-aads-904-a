#include <iostream>
#include <fstream>
#include "infix-expression.hpp"

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
    std::getline(std::cin, line);
    chemodurov::InfixExpr * inf = new chemodurov::InfixExpr[line.size() / 2 + 1];
  }
  else
  {
    std::ifstream input(argv[1]);
    if (!input.is_open())
    {
      std::cerr << "Error while reading\n";
      return 1;
    }
    size_t inf_size = 0;
    do
    {
      std::getline(input, line);
      chemodurov::InfixExpr * inf = new chemodurov::InfixExpr[line.size() / 2 + 1];
      size_t size1 = 0;
      size_t size2 = 0;
      while (size1)
      try
      {
        int a = std::stoi(line, std::addressof(size1));
        size1 += size2;
        size_t temp = size1;
        size1 = size2;
        size2 = temp;
        inf[inf_size++] = {a, true, false};
      }
      catch (const std::invalid_argument & e)
      {
        bool isBrace = false;
        if (line[size1] == '(' || line[size1] == ')')
        {
          isBrace = true;
        }
        inf[inf_size++] = {line[size1], false, !isBrace};
      }
    }
    while (input);
  }
  return 0;
}