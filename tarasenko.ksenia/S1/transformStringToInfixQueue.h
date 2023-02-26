#ifndef TRANSFORMSTRINGTOINFIXQUEUE_H
#define TRANSFORMSTRINGTOINFIXQUEUE_H
#include <string>
#include <cctype>
#include <stdexcept>
#include "queue.h"
#include "elem.h"

bool isdigit(std::string str)
{
  if (str.size() == 1)
  {
    if (std::isdigit(str[0])) return true;
  }
  else if ((std::isdigit(str[0]) || str[0] == '-' || str[0] == '+') && isdigit(str.erase(0,1)))
  {
    return true;
  }
  return false;
}

template< typename T >
Queue< T > transformStringToInfixQueue(std::string str)
{
  Queue< T > q_infix;
  Elem elem;
  size_t i = 0;

  while (i < str.size())
  {
    std::string element = "";
    while (!std::isspace(str[i]) && i < str.size())
    {
      element += str[i];
      i++;
    }
    if (isdigit(element))
    {
      elem.union_elem.operand = std::stoi(element);
      elem.is_int = true;
    }
    else if (element.size() == 1 && element.find_first_of("()-+/*%") != std::string::npos)
    {
      elem.union_elem.operation = element[0];
      elem.is_int = false;
    }
    else
    {
      throw std::logic_error("Incorrect input");
    }
    q_infix.push(elem);
    i++;
  }
  return q_infix;
}

#endif
