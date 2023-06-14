#include "divideExpression.h"

size_t checkPriority(char& operation)
{
  if (operation == '*' || operation == '/')
  {
    return 1;
  }
  return 0;
}
