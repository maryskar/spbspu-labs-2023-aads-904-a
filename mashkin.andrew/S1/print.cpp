#include "print.h"
#include <string>
#include <iostream>
#include "stack.h"

void print(mashkin::Stack< std::string >& res)
{
  while (res.isEmpty())
  {
    std::cout << res.drop();
    if (res.isEmpty())
    {
      std::cout << " ";
    }
  }
}
