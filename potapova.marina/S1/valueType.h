#ifndef VALUETYPE_H
#define VALUETYPE_H

#include <cstdint>
#include "queue.h"
#include "stack.h"

using expr_queue = potapova::Queue< potapova::ArithmExpMember >;
using expr_stack = potapova::Stack< potapova::ArithmExpMember >;

namespace potapova
{
  struct ArithmExpMember
  {
    enum class Type
    {
      Num,
      Operation
    };

    union
    {
      std::int64_t num;
      char operation;
    };

    Type type;
  };
}

#endif
