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
    do
    {
      std::getline(input, line);
      if (!input)
      {
        break;
      }
      size_t inf_size = 0;
      chemodurov::InfixExpr * inf = new chemodurov::InfixExpr[line.size() / 2 + 1];
      size_t size1 = 0;
      size_t size2 = 0;
      while (size2 < line.size())
      {
        try
        {
          int a = std::stoi(line, std::addressof(size1));
          size1 += size2;
          size2 = size1;
          inf[inf_size++] = {a, true, false};
        }
        catch (const std::invalid_argument & e)
        {
          if (line[size1] == '(')
          {
            inf[inf_size++] = {chemodurov::BRACE_LEFT, false, false};
          }
          else if (line[size1] == ')')
          {
            inf[inf_size++] = {chemodurov::BRACE_RIGHT, false, false};
          }
          else if (line[size1] == '+')
          {
            inf[inf_size++] = {chemodurov::OPERATION_PLUS, false, true};
          }
          else if (line[size1] == '-')
          {
            inf[inf_size++] = {chemodurov::OPERATION_MINUS, false, true};
          }
          else if (line[size1] == '*')
          {
            inf[inf_size++] = {chemodurov::OPERATION_MULTIPLICATION, false, true};
          }
          else if (line[size1] == '/')
          {
            inf[inf_size++] = {chemodurov::OPERATION_DIVIDE, false, true};
          }
          else if (line[size1] == '%')
          {
            inf[inf_size++] = {chemodurov::OPERATION_REMINDER_OF_DIVISION, false, true};
          }
          else
          {
            std::cerr << "Wrong input\n";
            return 1;
          }
        }
      }
      delete [] inf;
    }
    while (input);
  }
  return 0;
}