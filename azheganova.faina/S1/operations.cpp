#include "operations.h"
#include <stdexcept>

int getPriority(char operation)
{
  switch (operation)
  {
    case '(':
      return 0;
    case ')':
      return 1;
    case '+': case '-':
      return 2;
    case '*': case '/':
      return 3;
    default:
      throw std::invalid_argument("error");
  }
}

template< typename T >
T getOperation(T firstnum, T secondnum, char operation)
{
  if (operation == '+')
  {
    return firstnum + secondnum;
  }
  if (operation == '-')
  {
    return firstnum - secondnum;
  }
  if (operation == '*')
  {
    return firstnum * secondnum;
  }
  if (operation == '/')
  {
    if (secondnum == 0)
    {
      throw std::logic_error("division by 0");
    }
    return firstnum / secondnum;
  }
  if (operation == '%')
  {
    if (secondnum == 0)
    {
      throw std::logic_error("division by 0");
    }
    return firstnum % secondnum;
  }
}
