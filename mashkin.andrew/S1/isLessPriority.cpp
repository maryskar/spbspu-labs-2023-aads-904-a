#include "isLessPriority.h"

short int returnNumbOfOper(const std::string& var)
{
  if (var == "(")
  {
    return 0;
  }
  else if (var == "+" || var == "-")
  {
    return 1;
  }
  else
  {
    return 2;
  }
}

namespace mashkin
{
  bool isLessPriority(const std::string& op1, const std::string& op2)
  {
    short int left = returnNumbOfOper(op1);
    short int right = returnNumbOfOper(op2);
    return left >= right;
  }
}
