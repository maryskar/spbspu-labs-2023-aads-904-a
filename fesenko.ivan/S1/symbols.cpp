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
