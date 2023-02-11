#include "part.h"
dimkashelk::part dimkashelk::makePart(std::string str)
{
  std::string data("+-*/()%");
  part p;
  if (str.size() == 1 && data.find(str) != std::string::npos)
  {
    p.isDigit_ = false;
    p.operand_ = 0;
    p.operator_ = str[0];
  }
  else
  {
    p.isDigit_ = true;
    p.operand_ = std::stoi(str);
    p.operator_ = '+';
  }
  return p;
}
dimkashelk::part dimkashelk::makePart(int number)
{
  part p;
  p.isDigit_ = true;
  p.operand_ = number;
  p.operator_ = '+';
  return p;
}
