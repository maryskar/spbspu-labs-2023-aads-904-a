#ifndef CONVERTFROMINFIXTOPOSTFIX_H
#define CONVERTFROMINFIXTOPOSTFIX_H
#include <string>
#include "queue.h"
#include "stack.h"

namespace azheganova
{
  bool isPriority(std::string oper1, std::string oper2);
  Queue< std::string > convertFromInfixToPostfix(Queue< std::string > & infixqueue);
}

#endif
