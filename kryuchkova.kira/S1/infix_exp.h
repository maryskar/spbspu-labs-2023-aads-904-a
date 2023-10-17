#ifndef INFIX_EXP_H
#define INFIX_EXP_H

#include "part_of_exp.h"
#include "queue.h"

namespace kryuchkova
{
  Queue< ExpressionMember > getInfixExp(std::string &str);
}

#endif
