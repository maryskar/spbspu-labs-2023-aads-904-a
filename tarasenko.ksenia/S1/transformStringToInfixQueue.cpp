#include "transformStringToInfixQueue.h"
#include <cctype>

tarasenko::Queue< tarasenko::Elem > tarasenko::transformStringToInfixQueue(std::string str)
{
  Queue< Elem > q_infix;
  size_t i = 0;
  while (i < str.size())
  {
    std::string element = "";
    while (!std::isspace(str[i]) && i < str.size())
    {
      element += str[i];
      i++;
    }
    if (element.size() == 1 && element.find_first_of("()-+/*%") != std::string::npos)
    {
      MathSymbols ms(element[0]);
      Elem elem(ms);
      q_infix.push(elem);
    }
    else
    {
      Elem elem(std::stoll(element));
      q_infix.push(elem);
    }
    i++;
  }
  return q_infix;
}
