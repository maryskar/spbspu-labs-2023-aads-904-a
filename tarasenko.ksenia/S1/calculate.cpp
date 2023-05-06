#include "calculate.h"
#include <stdexcept>
#include "mathfunc.h"

long long tarasenko::calculate(long long a, long long b, char op)
{
  switch (op)
  {
    case '+':
      return summarize(a, b);
    case '-':
      return subtract(a, b);
    case '*':
      return multiply(a, b);
    case '/':
    {
      return divide(a, b);
    }
    case '%':
      return mod(a, b);
    default:
      throw std::invalid_argument("Incorrect input");
  }
}
