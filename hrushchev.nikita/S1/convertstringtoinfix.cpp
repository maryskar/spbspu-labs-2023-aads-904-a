#include "convertstringtoinfix.hpp"
#include <string>
#include <cstring>
#include <cstddef>
#include "queue.hpp"

Queue< std::string > convertStringToInfix(std::string str)
{
  Queue< std::string > infix_queue;
  for(size_t i = 0; str[i] != '\0'; i++)
  {
    infix_queue.push(str.substr(i, 1));
  }
  return infix_queue;
}

