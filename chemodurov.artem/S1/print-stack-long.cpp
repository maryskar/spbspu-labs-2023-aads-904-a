#include "print-stack-long.hpp"
#include <iostream>

void chemodurov::printStackLong(std::ostream & out, Stack< long > & stack)
{
  if (stack.empty())
  {
    throw std::invalid_argument("Nothing to print");
  }
  out << stack.getFromStack();
  stack.pop();
  while (!stack.empty())
  {
    out << ' ' << stack.getFromStack();
    stack.pop();
  }
}
