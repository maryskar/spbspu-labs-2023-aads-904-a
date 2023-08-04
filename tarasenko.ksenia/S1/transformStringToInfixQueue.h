#ifndef TRANSFORMSTRINGTOINFIXQUEUE_H
#define TRANSFORMSTRINGTOINFIXQUEUE_H
#include <string>
#include "queue.h"
#include "elem.h"
namespace tarasenko
{
  Queue< Elem > transformStringToInfixQueue(std::string str);
}
#endif
