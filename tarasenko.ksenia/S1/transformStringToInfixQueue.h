#ifndef TRANSFORMSTRINGTOINFIXQUEUE_H
#define TRANSFORMSTRINGTOINFIXQUEUE_H
#include <string>
#include <cctype>
#include "queue.h"
#include "elem.h"
namespace tarasenko
{
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
      if (element.size() == 1 && element.find_first_of("()-+/*%") != std::string::npos)
      {
        Operation op(element[0]);
        Elem elem(op);
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
}
#endif
