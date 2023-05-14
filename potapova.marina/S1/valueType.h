#ifndef VALUETYPE_H
#define VALUETYPE_H

#include <cstdint>

namespace potapova
{
  union Value
  {
    std::int64_t num;
    char operation;
  };

  enum class ValueType
  {
    Num,
    Operation 
  };

  Value value;
  ValueType type;
}

#endif
