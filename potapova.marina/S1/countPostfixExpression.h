#ifndef COUNTPOSTFIXEXPRESSION_H
#define COUNTPOSTFIXEXPRESSION_H

#include <cstdint>
#include "valueType.h"

namespace potapova
{
  std::int64_t countPostfixExpression(expr_queue& postfix_queue);
}

#endif
