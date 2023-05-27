#include "print.h"
#include <iostream>
#include "stack.h"

namespace mashkin
{
  void print(mashkin::Stack< int long long > res)
  {
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
