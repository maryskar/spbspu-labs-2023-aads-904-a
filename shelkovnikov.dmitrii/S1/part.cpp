#include "part.h"
dimkashelk::part::part(std::string str)
{
  std::string data("+-*/()%");
  if (str.size() == 1 && data.find(str) != std::string::npos)
  {
    isDigit_ = false;
    element_.operator_ = str[0];
  }
  else
  {
    isDigit_ = true;
    element_.operand_ = std::stoll(str);
  }
}
dimkashelk::part::part(long long number)
{
  isDigit_ = true;
  element_.operand_ = number;
}
