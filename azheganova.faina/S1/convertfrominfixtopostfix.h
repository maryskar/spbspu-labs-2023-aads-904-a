#ifndef CONVERTFROMINFIXTOPOSTFIX_H
#define CONVERTFROMINFIXTOPOSTFIX_H
#include <string>
#include "queue.h"

bool isDigit(const std::string & str);
bool isOperator(const std::string & oper);
Queue< std::string > convertFromInfixToPostfix(Queue< std::string > queue);

#endif
