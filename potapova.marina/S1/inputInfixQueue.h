#ifndef INPUTINFIXQUEUE_H
#define INPUTINFIXQUEUE_H

#include <iostream>
#include "valueType.h"

namespace potapova
{
  std::istream& inputInfixQueue(expr_queue& dest, std::istream& in);
}

#endif
