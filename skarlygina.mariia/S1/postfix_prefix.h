#ifndef POSTFIX_PREFIX_H
#define POSTFIX_PREFIX_H
#include "queue.h"
#include "stack.h"
namespace operation
{
  Queue< std::string > makePostfix(Queue< std::string >& infix_queue);
  Queue< std::string > makePrefix(Queue< std::string >& infix_queue);
}
#endif
