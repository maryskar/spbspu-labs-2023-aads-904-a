#ifndef VALUETYPE_H
#define VALUETYPE_H

#include <cstdint>

namespace potapova
{
  struct ArithmExpMember
  {
    enum class Type
    {
      Num,
      Operation
    };

    union Value
    {
      std::int64_t num;
      char operation;
    };

    Type type;
  };
}

#endif
