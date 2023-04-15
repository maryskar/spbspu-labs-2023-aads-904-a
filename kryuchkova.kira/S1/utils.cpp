#include "utils.h"
#include <stdexcept>
#include <cctype>

namespace kryuchkova
{
  int GetPriority(const char data)
  {
    if (!std::isdigit(data))
    {
      throw std::runtime_error("isn't digit");
    }
    else
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
        return 4;
      }
    }
  }
}
