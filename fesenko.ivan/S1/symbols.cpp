#include "symbols.h"

bool isOpenedBracket(std::string s)
{
  return s == "(";
}

bool isClosedBracket(std::string s)
{
  return s == ")";
}

bool isOperation(std::string s)
{
  return s == "+" || s == "-" || s == "*" || s == "/" || s == "%";
}

bool isNumber(std::string s)
{
  return !isOpenedBracket(s) && !isClosedBracket(s) && !isOperation(s);
}

size_t priority(std::string s)
{
  if (s == "+" || s == "-") {
    return 0;
  } else {
    return 1;
  }
}
