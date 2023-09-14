#include "count.h"
#include "calculator.h"
long long switchSymbol(const std::string& operation, long long a, long long b)
{
  long long result;
  if (operation == "-")
  {
    result = skarlygina::substraction(a, b);
  }
  if (operation == "+")
  {
    result = skarlygina::sum(a, b);
  }
  if (operation == "*")
  {
    result = skarlygina::multiplication(a, b);
  }
  if (operation == "/")
  {
    result = skarlygina::division(a, b);
  }
  if (operation == "%")
  {
    result = skarlygina::remainder(a, b);
  }
  return result;
}
