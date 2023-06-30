#ifndef DIVIDEEXPRESSION_H
#define DIVIDEEXPRESSION_H

#include <cstddef>
#include <string>
#include "queue.h"
#include "valueType.h"

namespace potapova
{
  expr_queue composePostfixQueue(expr_queue& infix_expr);
}

#endif
