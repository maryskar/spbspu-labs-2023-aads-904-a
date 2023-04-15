#ifndef GET_EXP_H
#define GET_EXP_H

#include "queue.h"
#include "stack.h"
#include "utils.h"

namespace kryuchkova
{
  void stringToInfix(std::string & str, Queue < long long > & inf);
  void infixToPostfix(Queue < long long > & inf, Queue < long long > &post);
  long long getResult(Queue < long long > & post);
}

#endif
