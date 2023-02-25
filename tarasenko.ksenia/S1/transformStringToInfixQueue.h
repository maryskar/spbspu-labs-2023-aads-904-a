#ifndef TRANSFORMSTRINGTOINFIXQUEUE_H
#define TRANSFORMSTRINGTOINFIXQUEUE_H
#include <string>
#include "queue.h"
#include <cctype>
#include "elem.h"

template< typename T >
Queue< T > transformStringToInfixQueue(std::string str)
{
  Queue< T > q_infix;
  Elem elem;
  size_t i = 0;
  while (i < str.size())
  {
    if (!std::isspace(str[i]))
    {
      std::string digit = "";
      if (!std::isdigit(str[i]))
      {
        elem.union_elem.operation = str[i];
        elem.is_int = false;
        i++;
      }
      else
      {
        do
        {
          digit += str[i];
          i++;
        }
        while (std::isdigit(str[i]));
        elem.union_elem.operand = std::stoi(digit);
        elem.is_int = true;
      }
      q_infix.push(elem);
    }
    else
    {
      i++;
    }
  }
  return q_infix;
}

#endif
