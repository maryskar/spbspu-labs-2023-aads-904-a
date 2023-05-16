#ifndef CONVERTFROMINFIXTOPOSTFIX_H
#define CONVERTFROMINFIXTOPOSTFIX_H
#include <string>
#include "queue.h"
#include "stack.h"

using queue_str = azheganova::Queue< std::string >;
using stack_str = azheganova::Stack< std::string >;

namespace azheganova
{
  bool getPriority(std::string oper);
  void convertFromInfixToPostfix(queue_str & queue, stack_str & stack, queue_str & postfix);
}

#endif
