#include "read-infix-expr.hpp"
#include <string>

chemodurov::Queue< chemodurov::InfixExpr > chemodurov::readInfixExpr(std::string & line)
{
  Queue< InfixExpr > inf;
  size_t size1 = 0;
  size_t size2 = 0;
  while (size2 < line.size())
  {
    if (line[size2] == '(')
    {
      InfixExpr temp(BRACE_LEFT);
      inf.push(temp);
      size2 += 2;
    }
    else if (line[size2] == ')')
    {
      InfixExpr temp(BRACE_RIGHT);
      inf.push(temp);
      size2 += 2;
    }
    else if (line[size2] == '+')
    {
      InfixExpr temp(OPERATION_PLUS);
      inf.push(temp);
      size2 += 2;
    }
    else if (line[size2] == '-')
    {
      InfixExpr temp(OPERATION_MINUS);
      inf.push(temp);
      size2 += 2;
    }
    else if (line[size2] == '*')
    {
      InfixExpr temp(OPERATION_MULTIPLICATION);
      inf.push(temp);
      size2 += 2;
    }
    else if (line[size2] == '/')
    {
      InfixExpr temp(OPERATION_DIVIDE);
      inf.push(temp);
      size2 += 2;
    }
    else if (line[size2] == '%')
    {
      InfixExpr temp(OPERATION_REMINDER_OF_DIVISION);
      inf.push(temp);
      size2 += 2;
    }
    else if (line[size2] == ' ')
    {
      ++size2;
    }
    else
    {
      long a = std::stol(line.substr(size2), std::addressof(size1));
      size1 += size2;
      size2 = size1;
      InfixExpr temp(a);
      inf.push(temp);
    }
  }
  return inf;
}
