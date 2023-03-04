#ifndef NOTATIONS_H
#define NOTATIONS_H
#include "queue.h"
bool isOperator(const std::string &c);
bool operationStackPopCondition(const std::string &q, const std::string &s);
void getPostfixFromInfix(Queue< std::string > *postfixQueue, Queue< std::string > *queue);
std::basic_string< char > calcPostfixExpression(Queue< std::string > postfixQueue);
Queue< Node<std::string> > *splitLine(Queue< std::string > * queue, const std::string &string);
#endif
