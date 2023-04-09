#include <iostream>
#include <string>
#include "calculator.h"
#include "stack.h"

int main()
{
  try
  {
    while (!std::cin.eof())
    {
      std::cout << calculateTheExpression(std::cin) << '\n';
    }
  }
  catch (const std::exception& e)
  {
    std::cout << e.what() << '\n';
    return 1;
  }


  return 0;
}
