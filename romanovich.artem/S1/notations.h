#ifndef NOTATIONS_H
#define NOTATIONS_H
#include "queue.h"
bool isOperator(const std::string &c);
bool operationStackPopCondition(const std::string &q, const std::string &s);
void parseQueue(Queue< std::string > *postfixQueue, Queue< std::string > *queue);
Queue< std::string > splitLine(const std::string &string);
#endif
