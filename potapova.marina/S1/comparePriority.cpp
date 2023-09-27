#include "comparePriority.h"
#include <cstddef>

size_t getPriority(const char operation)
{
  if (operation == '*' || operation == '/' || operation == '%')
  {
    return 1;
  }
  return 0;
}

bool potapova::comparePriority(const char first, const char second)
{
  return getPriority(first) < getPriority(second);
}
