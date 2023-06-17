#ifndef VALUETYPE_H
#define VALUETYPE_H

#include <cstdint>
#include "queue.h"
#include "stack.h"

namespace potapova
{
  struct ArithmExpMember;
  using expr_queue = Queue< ArithmExpMember >;

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

    ArithmExpMember();
    ArithmExpMember(std::int64_t num);
    ArithmExpMember(char operation);
  };
}

#endif
