#ifndef VALUETYPE_H
#define VALUETYPE_H

#include <cstdint>
#include "queue.h"

namespace potapova
{
  struct ArithmExpMember;
  using expr_queue = Queue< ArithmExpMember >;

  struct ArithmExpMember
  {
    enum class Type: std::uint8_t
    {
      Num,
      Operation
    };

    union
    {
      long long num;
      char operation;
    };

    Type type;

    ArithmExpMember();
    explicit ArithmExpMember(long long num);
    explicit ArithmExpMember(char operation);
  };
}

#endif
