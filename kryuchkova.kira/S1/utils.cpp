#include "utils.h"
#include <stdexcept>
#include <cctype>
#include <string>

namespace kryuchkova
{
  int GetPriority(std::string data)
  {
    if (data[0] == '+' || data[0] == '-' || data[0] == '/' || data[0] == '*')
    {
      return 2;
    }
    if (data[0] == '(' || data[0] == ')')
    {
      return 1;
    }
    else
    {
      if (!std::isdigit(data[0]) && data[0] != ' ')
      {
        throw std::runtime_error("isn't digit");
      }
      return 3;
    }
  }

  long long calculate(long long a, long long b, std::string operator_)
  {
    if (operator_[0] == '+')
    {
      return a + b;
    }
    else if (operator_[0] == '-')
    {
      return a - b;
    }
    else if (operator_[0] == '*')
    {
      return a * b;
    }
    else if (operator_[0] == '/')
    {
      if (b == 0)
      {
        throw std::logic_error("division by zero");
      }
      return a / b;
    }
    else if (operator_[0] == '%')
    {
      if (b == 0)
      {
        throw std::logic_error("division by zero");
      }
      return a % b;
    }
    return a + b;
  }
}
