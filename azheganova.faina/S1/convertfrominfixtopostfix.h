#ifndef CONVERTFROMINFIXTOPOSTFIX_H
#define CONVERTFROMINFIXTOPOSTFIX_H
#include <string>
#include "queue.h"

bool isOperator(const std::string & oper);
bool checkPriority(const std::string & priority1, const std::string & priority2);
Queue< std::string > convertFromInfixToPostfix(Queue< std::string > queue);

#endif
