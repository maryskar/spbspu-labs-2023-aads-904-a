#ifndef CONVERTFROMINFIXTOPOSTFIX_H
#define CONVERTFROMINFIXTOPOSTFIX_H
#include <string>
#include "queue.h"
#include "stack.h"

bool isOperator(std::string oper);
void convertFromInfixToPostfix(Queue< std::string > & queue, Stack< std::string > & stack, Queue< std::string > & postfix);

#endif
