#include "utils.h"
#include <stdexcept>
#include <cctype>

namespace kryuchkova
{
  int GetPriority(const char data)
  {
    if (data == '+' || data == '-')
    {
      return 3;
    }
    if (data == '/' || data == '*')
    {
      return 2;
    }
    if (data == '(' || data == ')')
    {
      return 1;
    }
    else
    {
      if (!std::isdigit(data))
      {
        throw std::runtime_error("isn't digit");
      }
      return 4;
    }
  }

  long long calculate(long long a, long long b, char operand)
  {
    if (operand == '+')
    {
      return a + b;
    }
    if (operand == '-')
    {
      return a - b;
    }
    if (operand == '*')
    {
      return a * b;
    }
    if (operand == '/')
    {
      if (b == 0)
      {
        throw std::logic_error("division by zero");
      }
      return a / b;
    }
    if (operand == '%')
    {
      if (b == 0)
      {
        throw std::logic_error("division by zero");
      }
      return a % b;
    }
  }
}
