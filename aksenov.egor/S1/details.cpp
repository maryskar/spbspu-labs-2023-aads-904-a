#include "details.h"
bool isNumeric(std::string const &str)
{
  char* p = nullptr;
  std::strtol(str.c_str(), &p, 10);
  return *p == 0;
}
bool isOperator(std::string oper)
{
  return oper == "+" || oper == "-" || oper == "*" || oper == "/" || oper == "%";
}
int getPriority(std::string operation)
{
  if (operation == "+" || operation == "-")
  {
    return 1;
  }
  else if (operation == "*" || operation == "/" || operation == "%")
  {
    return 2;
  }
  else
  {
    return 0;
  }
}
