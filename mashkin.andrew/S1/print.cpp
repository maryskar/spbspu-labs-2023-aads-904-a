#include "print.h"
#include <iostream>
#include <string>
#include "stack.h"

namespace mashkin
{
  void print(mashkin::Stack< int long long >& result)
  {
    while (result.isEmpty())
    {
      std::cout << result.getTop();
      result.pop();
      if (result.isEmpty())
      {
        std::cout << " ";
      }
    }
  }
}
