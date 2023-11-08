#ifndef OPERATIONS_PARENTHESES_H
#define OPERATIONS_PARENTHESES_H

namespace kryuchkova
{
  enum class operation_t: char
  {
    SUBTRACTION = '-',
    ADDITION = '+',
    MULTIPLICATION = '*',
    DIVISION = '/',
    EUCLIDEAN_DIVISION = '%'
  };

  enum class parenthesis_t: char
  {
    OPEN = '(',
    CLOSE = ')'
  };
}

#endif
