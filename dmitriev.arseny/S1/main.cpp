#include <iostream>
#include "stack.h"

int main()
{
  Stack< int > a;

  try
  {
    a.push(1);
    a.push(2);

    std::cout << a.getTopData() << '\n';
    std::cout << a.unsafeGetTopAndPop() << '\n';
    std::cout << a.unsafeGetTopAndPop() << '\n';

    a.push(3);
    std::cout << a.getTopData() << '\n';
    std::cout << a.unsafeGetTopAndPop() << '\n';
    std::cout << a.unsafeGetTopAndPop() << '\n';
  }
  catch (const std::exception& e)
  {
    std::cout << e.what() << '\n';
    return 1;
  }


  return 0;
}
