#ifndef CALCULATE_H
#define CALCULATE_H
#include <stdexcept>

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
        throw std::logic_error("Division by zero\n");
      }
      return a / b;
    }
    case '%':
      return a % b;
    default:
      throw std::invalid_argument("Incorrect input\n");
  }
}

#endif
