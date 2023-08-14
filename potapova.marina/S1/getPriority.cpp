#include "getPriority.h"

size_t potapova::getPriority(const char operation)
  {
    if (operation == '*' || operation == '/' || operation == '%')
    {
      return 1;
    }
    return 0;
  }
