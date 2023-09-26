#include "operations.h"

bool kozyrin::isLowPriority(const std::string& a)
{
  return a == "-" || a == "+";
}

bool kozyrin::isHighPriority(const std::string& a)
{
  return a == "*" || a == "/" || a == "%";
}

bool kozyrin::isLowerPriority(const std::string& a, const std::string& b)
{
  return isLowPriority(a) && isHighPriority(b);
}

bool kozyrin::isOperation(const std::string& chr)
{
  return chr == "+" || chr == "-" || chr == "/" || chr == "*" || chr == "%";
}
