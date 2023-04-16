#include "check_exp.h"
#include <limits>
#include <stdexcept>
#include <string>
#include "utils.h"

namespace kryuchkova
{

  long long maximum = std::numeric_limits< long long >::max();
  long long minimum = std::numeric_limits< long long >::min();

  void isOverflow(long long data)
  {
    if (data > maximum || data < minimum)
    {
      throw std::overflow_error("Overflow");
    }
  }

  void incorrectString(std::string & str)
  {
    size_t size = str.size();
    for (size_t i; i < size - 1; i++)
    {
      if (isdigit(str[i]) && isdigit(str[i + 1]))
      {
        throw std::logic_error("Wrong expression (two numbers)");
      }
      if (!(isdigit(str[i]) || isdigit(str[i + 1])))
      {
        throw std::logic_error("Wrong expression (two signs)");
      }
    }
  }

}
