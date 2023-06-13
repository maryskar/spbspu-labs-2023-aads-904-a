#include "symbols.h"

bool fesenko::isOpenedBracket(std::string s)
{
  return s == "(";
}

bool fesenko::isClosedBracket(std::string s)
{
  return s == ")";
}

bool fesenko::isOperation(std::string s)
{
  return s == "+" || s == "-" || s == "*" || s == "/" || s == "%";
}

bool fesenko::isNumber(std::string s)
{
  return !isOpenedBracket(s) && !isClosedBracket(s) && !isOperation(s);
}

size_t fesenko::priority(std::string s)
{
  if (s == "+" || s == "-") {
    return 1;
  } else {
    return 0;
  }
}
