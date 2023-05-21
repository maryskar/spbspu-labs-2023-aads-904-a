#ifndef COUNT_POSTFIX_H
#define COUNT_POSTFIX_H
#include "queue.h"
#include "stack.h"
template< typename T >
long long countPostfix(Queue< T >& postfix_queue)
{
  Stack< long long > elem;
  while (!postfix_queue.isEmpty())
  {
    std::string token = postfix_queue.get();
    postfix_queue.pop();
  }
}
#endif
