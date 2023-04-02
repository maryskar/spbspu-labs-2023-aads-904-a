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
  int a = 2;
  queue.push(a);
  queue.push(a + 1);
  std::cout << queue.drop() << queue.drop() << '\n';
  return 0;
}
