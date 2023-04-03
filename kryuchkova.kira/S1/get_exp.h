#ifndef GET_EXP_H
#define GET_EXP_H

#include "queue.h"
#include "stack.h"
#include "calc_data_type.h"

namespace kryuchkova
{
  void stringToInfix(std::string & str, calc_data_type data);
  void InfixToPostfix();
}

#endif
