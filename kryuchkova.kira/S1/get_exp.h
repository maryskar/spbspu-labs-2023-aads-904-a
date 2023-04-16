#ifndef GET_EXP_H
#define GET_EXP_H

#include "queue.h"
#include "stack.h"
#include "utils.h"
#include <string>

namespace kryuchkova
{
  void stringToInfix(std::string & str, Queue < std::string > & inf);
  void infixToPostfix(Queue < std::string > & inf, Queue < std::string > &post);
  long long getResult(Queue < std::string > & post);
}

#endif
