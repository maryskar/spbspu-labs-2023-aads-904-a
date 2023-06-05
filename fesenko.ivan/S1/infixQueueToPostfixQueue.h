#ifndef INFIXQUEUETOPOSTFIXQUEUE_H
#define INFIXQUEUETOPOSTFIXQUEUE_H
#include <string>
#include "queue.h"
namespace fesenko
{
  Queue< std::string > infixQueueToPostfixQueue(Queue < std::string > &infixQueue);
}
#endif
