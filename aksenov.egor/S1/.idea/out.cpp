#include "out.h"
#include <iostream>
void out(aksenov::Stack< long long > &result)
{
  while (!result.isEmpty())
  {
    std::cout << result.drop();
    result.pop();
    if (!result.isEmpty())
    {
      std::cout << " ";
    }
  }
}
