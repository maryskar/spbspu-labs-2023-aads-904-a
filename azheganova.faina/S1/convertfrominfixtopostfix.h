#ifndef CONVERTFROMINFIXTOPOSTFIX_H
#define CONVERTFROMINFIXTOPOSTFIX_H
#include <string>
#include "queue.h"

bool isDigit(const std::string & string);
bool isOperator(std::string oper);
Queue< std::string > convertFromInfixToPostfix(Queue< std::string > & queue);

#endif
