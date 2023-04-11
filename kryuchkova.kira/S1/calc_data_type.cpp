#include "calc_data_type.h"
#include <stdexcept>
#include <cctype>

namespace kryuchkova
{
  bool calc_data_type::isDigit(const char data)
  {
    return std::isdigit(data);
  }
  void calc_data_type::GetPriority(const char data)
  {
    int priority = 0;
    if (!isDigit(data))
    {
      throw std::runtime_error("isn't digit");
    }
    else
    {
      if (data == '+' || data == '-')
      {
        priority = 1;
      }
      if (data == '/' || data == '*')
      {
        priority = 2;
      }
      if (data == '(' || data == ')')
      {
        priority = 3;
      }
      //return priority;
    }
  }
}
