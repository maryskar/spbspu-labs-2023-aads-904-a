#ifndef COUNT_POSTFIX_H
#define COUNT_POSTFIX_H
#include <string>
#include "queue.h"
#include "stack.h"

namespace skarlygina
{
  void formatToPostfix(std::string& str, Queue< std::string >& queue);
  void countPostfix(Queue< std::string >& queue, Stack< long long > res);
}
#endif
