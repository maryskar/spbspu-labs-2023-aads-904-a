#ifndef OPERATIONS_H
#define OPERATIONS_H
#include <string>

bool isLowPriority(const std::string& a);
bool isHighPriority(const std::string& a);
bool isLowerPriority(const std::string& a, const std::string& b);
bool isOperation(const std::string& chr);

#endif
