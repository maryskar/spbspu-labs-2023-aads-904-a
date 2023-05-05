#include "print.h"
#include <iostream>
#include <string>
#include "stack.h"

namespace machkin
{
  void print(mashkin::Stack< std::string >& result)
  {
    while (result.isEmpty())
    {
      std::cout << result.drop() << " ";
      result.pop();
      if (result.isEmpty())
      {
        std::cout << " ";
      }
    }
  }
}
