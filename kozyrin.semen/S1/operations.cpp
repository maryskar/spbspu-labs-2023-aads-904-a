#include "operations.h"

bool isLowPriority(const std::string& a)
{
  return a == "-" || a == "+";
}

bool isHighPriority(const std::string& a)
{
  return a == "*" || a == "/" || a == "%";
}

bool isLowerPriority(const std::string& a, const std::string& b)
{
  return isLowPriority(a) && isHighPriority(b);
}

bool isOperation(const std::string& chr)
{
  return chr == "+" || chr == "-" || chr == "/" || chr == "*" || chr == "%";
}
