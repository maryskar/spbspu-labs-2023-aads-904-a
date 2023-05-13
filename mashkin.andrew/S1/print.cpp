#include "print.h"
#include <iostream>
#include "stack.h"

namespace mashkin
{
  void print(const mashkin::Stack< int long long >& result)
  {
    auto res = result;
    while (res.isEmpty())
    {
      std::cout << res.getTop();
      res.pop();
      if (res.isEmpty())
      {
        std::cout << " ";
      }
    }
  }
}
