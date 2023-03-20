#ifndef NOTATION_H
#define NOTATION_H
#include <iostream>
#include <fstream>
#include "queue.h"
#include "stack.h"

bool isNumber(std::string& str);
bool isLowPriority(const std::string& a);
bool isHighPriority(const std::string& a);
bool isLowerPriority(const std::string& a, const std::string& b);
bool isOperation(const std::string& chr);
int getPostfix(Queue< std::string >& queue, Queue< std::string >& input, std::ostream& errStream);

#endif
