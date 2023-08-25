#ifndef NOTATION_H
#define NOTATION_H
#include "queue.h"
#include "stack.h"

namespace kozyrin {
  Queue< std::string > getPostfix(Queue< std::string >& src);
}

#endif
