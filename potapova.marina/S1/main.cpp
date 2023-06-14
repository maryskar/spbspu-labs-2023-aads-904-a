#include <iostream>
#include "valueType.h"
#include "queue.h"
#include "getInfixQueue.h"

int main()
{
  potapova::Queue< potapova::ArithmExpMember > dest;
  std::istream& in = std::cin;
  if (!inputInfixQueue(dest, in))
  {
    std::cerr << "Input error\n";
    return 1;
  }
}
