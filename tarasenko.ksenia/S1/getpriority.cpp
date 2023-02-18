#include "getpriority.h"
#include <stdexcept>

int getPriority(char op)
{
  switch (op)
  {
    case '+': case '-':
      return 1;
    case '*': case '/': case '%':
      return 2;
    case '(': case ')':
      return 3;
    default:
      throw std::invalid_argument("Incorrect input\n");
  }
}
