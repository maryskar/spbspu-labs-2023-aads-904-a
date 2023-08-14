#include "valueType.h"

potapova::ArithmExpMember::ArithmExpMember():
  num(0),
  type(Type::Num)
{

}

potapova::ArithmExpMember::ArithmExpMember(long long num):
  num(num),
  type(Type::Num)
{

}

potapova::ArithmExpMember::ArithmExpMember(char operation):
  operation(operation),
  type(Type::Operation)
{

}
