#ifndef CONVERTFROMINFIXTOPOSTFIX_H
#define CONVERTFROMINFIXTOPOSTFIX_H
#include <string>
#include "queue.h"
#include "stack.h"

using q_n = azheganova::Queue< std::string >;
using s_n = azheganova::Stack< std::string >;
bool isOperator(std::string oper);
void convertFromInfixToPostfix(q_n & queue, s_n & stack, q_n & postfix);

#endif
