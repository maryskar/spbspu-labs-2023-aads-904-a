#include "priority.h"
#include <stdexcept>

bool azheganova::getPriority(std::string oper)
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

bool azheganova::isPriority(std::string oper1, std::string oper2)
{
  return std::less< bool >{}(getPriority(oper1), getPriority(oper2));
}
