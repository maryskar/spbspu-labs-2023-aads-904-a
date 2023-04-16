#ifndef CALCULATE_H
#define CALCULATE_H
#include "queue.h"
#include "stack.h"

std::string calculateOperations(long long secondnum, long long firstnum, const std::string & element);
void calculatePostfix(Queue <std::string> & postfix, Stack <std::string> & answer, Stack <std::string> & stack);

#endif
