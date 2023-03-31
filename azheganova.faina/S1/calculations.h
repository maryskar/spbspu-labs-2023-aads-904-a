#ifndef CALCULATIONS_H
#define CALCULATIONS_H

bool isOperator(const std::string & operator);
bool checkPriority(const std::string & n1, const std::string & n2);
Queue< std::string > convertFromInfixToPostfix(Queue< std::string > queue);

#endif