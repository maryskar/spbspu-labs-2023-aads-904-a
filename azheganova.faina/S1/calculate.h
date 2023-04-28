#ifndef CALCULATE_H
#define CALCULATE_H
#include "queue.h"
#include "stack.h"

using q_n = azheganova::Queue <std::string>;
using s_n = azheganova::Stack <std::string>;
std::string calculateOperations(long long secondnum, long long firstnum, const std::string & element);
void calculatePostfix(q_n & postfix, s_n & answer, s_n & stack);

#endif
