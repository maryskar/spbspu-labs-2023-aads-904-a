#ifndef COUNT_POSTFIX_H
#define COUNT_POSTFIX_H
#include "queue.h"
#include "stack.h"
#include "count.h"
template< typename T >
long long countPostfix(Queue< T >& postfix_queue)
{
  Stack< long long > stack;
  while (!postfix_queue.isEmpty())
  {
    std::string token = postfix_queue.get();
    postfix_queue.pop();
    if (isdigit(token[0]))
    {
      long long num = stoll(token);
      stack.push(num);
    }
    else
    {
      long long operand_second = stack.get();
      stack.pop();
      long long operand_first = stack.get();
      stack.pop();
      switchSymbol(token, operand_first, operand_second);
    }
  }
  return stack.get();
}
#endif
