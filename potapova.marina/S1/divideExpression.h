#ifndef DIVIDEEXPRESSION_H
#define DIVIDEEXPRESSION_H

#include <cstddef>
#include <string>
#include "queue.h"
#include "valueType.h"

namespace potapova
{
  size_t checkPriority(char& operation);
  potapova::Queue< potapova::ArithmExpMember >& potapova::composePostfixQueue(potapova::Queue< potapova::ArithmExpMember >& infix_expr);
}

#endif
