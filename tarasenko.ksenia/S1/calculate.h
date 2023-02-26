#ifndef CALCULATE_H
#define CALCULATE_H
#include <stdexcept>

int mod(int n, int d)
{
  int result = n % d;
  if (result * d < 0)
    result += d;
  return result;
}

template< typename T >
T calculate(T a, T b, char op)
{
  switch (op)
  {
    case '+':
      return a + b;
    case '-':
      return a - b;
    case '*':
      return a * b;
    case '/':
    {
      if (b == 0)
      {
        throw std::logic_error("Division by zero");
      }
      return a / b;
    }
    case '%':
      return mod(a, b);
    default:
      throw std::invalid_argument("Incorrect input");
  }
}

#endif
