#ifndef VALUETYPE_H
#define VALUETYPE_H

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
  if (type == ValueType::Operation)
  {
    value.operation;
  }
  else
  {
    value.num;
  }
}

#endif
