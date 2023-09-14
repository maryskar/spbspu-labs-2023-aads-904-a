#include "count.h"
#include <stdexcept>
#include "calculator.h"
long long switchSymbol(const std::string& operation, long long a, long long b)
{
  if (operation == "-")
  {
    return skarlygina::substraction(a, b);
  }
  else if (operation == "+")
  {
    return skarlygina::sum(a, b);
  }
  else if (operation == "*")
  {
    return skarlygina::multiplication(a, b);
  }
  else if (operation == "/")
  {
    return skarlygina::division(a, b);
  }
  else if (operation == "%")
  {
    return skarlygina::remainder(a, b);
  }
  else
  {
    throw std::runtime_error("Unknown operator");
  }
}
