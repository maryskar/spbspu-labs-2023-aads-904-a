#ifndef POSTFIX_PREFIX_H
#define POSTFIX_PREFIX_H
#include "queue.h"
#include "stack.h"
namespace operation
{
  Queue< std::string > makePostfix(Queue< std::string >& infixQueue);
  Queue< std::string > makePrefix(Queue< std::string >& infixQueue);
}
#endif
