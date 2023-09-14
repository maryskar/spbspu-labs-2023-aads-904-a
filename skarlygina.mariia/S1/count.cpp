#include "count.h"
#include <stdexcept>
#include "calculator.h"
long long switchSymbol(const std::string& operation, long long a, long long b)
{
  long long result;
  if (operation == "-")
  {
    return skarlygina::substraction(a, b);
  }
  if (operation == "+")
  {
    return skarlygina::sum(a, b);
  }
  if (operation == "*")
  {
    return skarlygina::multiplication(a, b);
  }
  if (operation == "/")
  {
    return skarlygina::division(a, b);
  }
  if (operation == "%")
  {
    return skarlygina::remainder(a, b);
  }
  else
  {
    throw std::runtime_error("Unknown operator");
  }
}
