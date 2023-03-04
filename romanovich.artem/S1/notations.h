#ifndef NOTATIONS_H
#define NOTATIONS_H
#include "queue.h"
bool isOperator(const std::string &c);
bool operationStackPopCondition(const std::string &q, const std::string &s);
Queue< std::string > getPostfixFromInfix(Queue< std::string > queue);
std::basic_string< char > calcPostfixExpression(Queue< std::string > postfixQueue);
Queue< std::string > splitLine(const std::string &string);
#endif
