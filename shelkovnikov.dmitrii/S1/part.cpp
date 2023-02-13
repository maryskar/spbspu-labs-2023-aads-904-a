#include "part.h"
dimkashelk::part dimkashelk::makePart(std::string str)
{
  std::string data("+-*/()%");
  part p;
  if (str.size() == 1 && data.find(str) != std::string::npos)
  {
    p.isDigit_ = false;
    p.element_.operator_ = str[0];
  }
  else
  {
    p.isDigit_ = true;
    p.element_.operand_ = std::stoll(str);
  }
  return p;
}
dimkashelk::part dimkashelk::makePart(long long number)
{
  part p;
  p.isDigit_ = true;
  p.element_.operand_ = number;
  return p;
}
