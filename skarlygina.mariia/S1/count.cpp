#include "count.h"
#include "calculator.h"
long long switchSymbol(char operation, long long a, long long b)
{
  switch (operation)
  {
  case '+':
    return calculator::sum(a, b);
  case '-':
    return calculator::substraction(a, b);
  case '*':
    return calculator::multiplication(a, b);
  case '/':
    return calculator::division(a, b);
  case '%':
    return calculator::remainder(a, b);
  default:
    throw;
  }
}
