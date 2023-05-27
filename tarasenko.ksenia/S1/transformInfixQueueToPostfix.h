#ifndef TRANSFORMINFIXQUEUETOPOSTFIX_H
#define TRANSFORMINFIXQUEUETOPOSTFIX_H
#include "queue.h"
#include "elem.h"
namespace tarasenko
{
  Queue< Elem > transformInfixQueueToPostfix(Queue< Elem >& q_infix);
}
#endif
