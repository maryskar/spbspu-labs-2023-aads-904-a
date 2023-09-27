#include "priority.h"
#include <stdexcept>

int getPriority(std::string oper)
{
  if (oper == ")")
  {
    return 0;
  }
  else if (oper == "(")
  {
    return 0;
  }
  else if (oper == "+")
  {
    return 1;
  }
  else if (oper == "-")
  {
    return 1;
  }
  else if (oper == "*")
  {
    return 2;
  }
  else if (oper == "/")
  {
    return 2;
  }
  else if (oper == "%")
  {
    return 2;
  }
  else if (oper == ")")
  {
    return 0;
  }
  else if (oper == "(")
  {
    return 0;
  }
  else
  {
    throw std::logic_error("error");
  }
}

bool azheganova::isLessPriority(std::string oper1, std::string oper2)
{
  return getPriority(oper1) >= getPriority(oper2);
}
