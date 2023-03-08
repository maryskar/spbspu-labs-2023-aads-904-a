#ifndef TRANSFORMSTRINGTOINFIXQUEUE_H
#define TRANSFORMSTRINGTOINFIXQUEUE_H
#include <string>
#include <cctype>
#include <stdexcept>
#include "queue.h"
#include "elem.h"
namespace tarasenko
{
  bool isDigit(std::string str)
  {
    if (str.size() == 1)
    {
      if (std::isdigit(str[0]))
      {
        return true;
      }
    }
    else if ((std::isdigit(str[0]) || str[0] == '-' || str[0] == '+') && isDigit(str.erase(0, 1)))
    {
      return true;
    }
    return false;
  }

  Queue< Elem > transformStringToInfixQueue(std::string str)
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
      if (isDigit(element))
      {
        Elem elem(std::stoll(element));
        q_infix.push(elem);
      }
      else if (element.size() == 1 && element.find_first_of("()-+/*%") != std::string::npos)
      {
        Operation op(element[0]);
        Elem elem(op);
        q_infix.push(elem);
      }
      else
      {
        throw std::logic_error("Incorrect input");
      }
      i++;
    }
    return q_infix;
  }
}
#endif
