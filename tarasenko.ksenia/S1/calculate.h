#ifndef CALCULATE_H
#define CALCULATE_H
#include "mathfunc.h"
namespace tarasenko
{
  template< typename T >
  T calculate(T a, T b, char op)
  {
    switch (op)
    {
      case '+':
        return summarize< T >(a, b);
      case '-':
        return subtract< T >(a, b);
      case '*':
        return multiply< T >(a, b);
      case '/':
      {
        return divide< T >(a, b);
      }
      case '%':
        return mod< T >(a, b);
      default:
        throw std::invalid_argument("Incorrect input");
    }
  }
}
#endif
