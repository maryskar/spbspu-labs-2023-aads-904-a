#ifndef INFIXEXPRESSIONCONVERSIONS_H
#define INFIXEXPRESSIONCONVERSIONS_H
#include <string>
#include "queue.h"

namespace chulkov {
  Queue< std::string > infixToPostfix(std::string& infix);
}

#endif
