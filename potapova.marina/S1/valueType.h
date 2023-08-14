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
      std::int64_t num;
      char operation;
    };

    Type type;

    ArithmExpMember();
    explicit ArithmExpMember(std::int64_t num);
    explicit ArithmExpMember(char operation);
  };
}

#endif
