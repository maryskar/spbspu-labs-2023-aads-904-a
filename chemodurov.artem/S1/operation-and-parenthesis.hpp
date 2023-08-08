#ifndef OPERATION_AND_PARENTHESIS_HPP
#define OPERATION_AND_PARENTHESIS_HPP

namespace chemodurov
{
  enum class operation_t: char
  {
    PLUS = '+',
    MINUS = '-',
    MULTIPLICATION = '*',
    DIVIDE = '/',
    REMINDER_OF_DIVISION = '%'
  };

  enum class parenthesis_t: char
  {
    LEFT = '(',
    RIGHT = ')'
  };
}

#endif
