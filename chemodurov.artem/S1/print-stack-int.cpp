#include "print-stack-int.hpp"
#include <iostream>

void chemodurov::printStackInt(std::ostream & out, Stack< int > stack)
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
