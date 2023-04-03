#include "queue.h"
#include "stack.h"
#include "node.h"
#include <iostream>

int main()
{
  //int a;
  // kryuchkova::Stack <int> stack;
  // std::cin >> a;
  // stack.push(a);
  // stack.push(a + 1);
  // int b = stack.drop();
  // std::cout << b << ' ' << stack.drop() << '\n';
  kryuchkova::Queue <int> queue;
  int a = 1;
  for (int i = 0; i < 5; i++)
  {
    std::cin >> a;
    queue.push(a);
  }
  while (!queue.isEmpty())
  {
    std::cout << queue.drop() << ' ';
  }
  return 0;
}
