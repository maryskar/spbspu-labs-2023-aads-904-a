#include "valueType.h"

potapova::ArithmExpMember::ArithmExpMember():
  num(0),
  type(Type::Num)
{

}

potapova::ArithmExpMember::ArithmExpMember(std::int64_t num):
  num(num),
  type(Type::Num)
{
  
}

potapova::ArithmExpMember::ArithmExpMember(char operation):
  operation(operation),
  type(Type::Operation)
{

}
