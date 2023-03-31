#include "operations.h"
#include <stdexcept>

int getPriority(char operation)
{
    if(operation == '+' || operation == '-')
    {
      return 1;
    }
    if(operation == '*' || operation == '/' || operation == '%')
    {
      return 2;
    }
  throw std::invalid_argument("error");
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
