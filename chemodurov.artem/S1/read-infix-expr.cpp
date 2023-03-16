#include "read-infix-expr.hpp"
#include <string>
#include <stdexcept>
#include <iostream>

chemodurov::InfixExpr * chemodurov::readInfixExpr(std::istream & in, size_t & inf_size)
{
  std::string line;
  std::getline(in, line);
  if (!in)
  {
    throw std::invalid_argument("Nothing to read");
  }
  chemodurov::InfixExpr * inf = new chemodurov::InfixExpr[line.size() / 2 + 1];
  inf_size = 0;
  size_t size1 = 0;
  size_t size2 = 0;
  while (size2 < line.size())
  {
    if (line[size2] == '(')
    {
      inf[inf_size++] = {chemodurov::BRACE_LEFT, false, false};
      ++size2;
    }
    else if (line[size2] == ')')
    {
      inf[inf_size++] = {chemodurov::BRACE_RIGHT, false, false};
      ++size2;
    }
    else if (line[size2] == '+')
    {
      inf[inf_size++] = {chemodurov::OPERATION_PLUS, false, true};
      ++size2;
    }
    else if (line[size2] == '-')
    {
      inf[inf_size++] = {chemodurov::OPERATION_MINUS, false, true};
      ++size2;
    }
    else if (line[size2] == '*')
    {
      inf[inf_size++] = {chemodurov::OPERATION_MULTIPLICATION, false, true};
      ++size2;
    }
    else if (line[size2] == '/')
    {
      inf[inf_size++] = {chemodurov::OPERATION_DIVIDE, false, true};
      ++size2;
    }
    else if (line[size2] == '%')
    {
      inf[inf_size++] = {chemodurov::OPERATION_REMINDER_OF_DIVISION, false, true};
      ++size2;
    }
    else if (line[size2] == ' ')
    {
      ++size2;
    }
    else
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
        delete [] inf;
        throw;
      }
    }
  }
  return inf;
}
