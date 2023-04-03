#ifndef GET_EXP_H
#define GET_EXP_H

#include "queue.h"
#include "stack.h"
#include "calc_data_type.h"

namespace kryuchkova
{
  void stringToInfix(std::string & str, Queue < calc_data_type > & inf);
  void infixToPostfix(Queue < calc_data_type > & inf, Queue < calc_data_type > &post);
  long long getResult(Queue < calc_data_type > & post);
}

#endif
