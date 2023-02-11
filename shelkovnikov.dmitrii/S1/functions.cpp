#include "functions.h"
bool dimkashelk::isPriorityOperation(char first, char second)
{
  if (first == '+' || first == '-')
  {
    return second == '*' || second == '/' || second == '%' || second == '(';
  }
  else
  {
    return second == '(';
  }
}
int dimkashelk::getResult(int first, int second, char oper)
{
  if (oper == '+')
  {
    return first + second;
  }
  if (oper == '-')
  {
    return first - second;
  }
  if (oper == '*')
  {
    return first * second;
  }
  if (oper == '/')
  {
    if (second == 0)
    {
      throw std::logic_error("Division by 0");
    }
    return first / second;
  }
  if (oper == '%')
  {
    if (first > 0)
    {
      return first % second;
    }
    else
    {
      return second - (-first) % second;
    }
  }
  throw std::logic_error("Not supported this operator");
}
