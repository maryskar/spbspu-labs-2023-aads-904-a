#include "read-infix-expr.hpp"
#include <string>

chemodurov::InfixExpr * chemodurov::readInfixExpr(std::string & line, size_t & inf_size)
{
  InfixExpr * inf = new InfixExpr[line.size() / 2 + 1];
  inf_size = 0;
  size_t size1 = 0;
  size_t size2 = 0;
  while (size2 < line.size())
  {
    if (line[size2] == '(')
    {
      inf[inf_size++] = {BRACE_LEFT, false, false};
      size2 += 2;
    }
    else if (line[size2] == ')')
    {
      inf[inf_size++] = {BRACE_RIGHT, false, false};
      size2 += 2;
    }
    else if (line[size2] == '+')
    {
      inf[inf_size++] = {OPERATION_PLUS, false, true};
      size2 += 2;
    }
    else if (line[size2] == '-')
    {
      inf[inf_size++] = {OPERATION_MINUS, false, true};
      size2 += 2;
    }
    else if (line[size2] == '*')
    {
      inf[inf_size++] = {OPERATION_MULTIPLICATION, false, true};
      size2 += 2;
    }
    else if (line[size2] == '/')
    {
      inf[inf_size++] = {OPERATION_DIVIDE, false, true};
      size2 += 2;
    }
    else if (line[size2] == '%')
    {
      inf[inf_size++] = {OPERATION_REMINDER_OF_DIVISION, false, true};
      size2 += 2;
    }
    else if (line[size2] == ' ')
    {
      ++size2;
    }
    else
    {
      try
      {
        long a = std::stol(line.substr(size2), std::addressof(size1));
        size1 += size2;
        size2 = size1;
        inf[inf_size++] = {a, true, false};
      }
      catch (const std::exception & e)
      {
        delete[] inf;
        throw;
      }
    }
  }
  return inf;
}
