#include "arithmExpressionMember.h"

potapova::ArithmExpMember::ArithmExpMember():
  num_(0),
  type_(Type::Num)
{

}

potapova::ArithmExpMember::ArithmExpMember(long long num):
  num_(num),
  type_(Type::Num)
{

}

potapova::ArithmExpMember::ArithmExpMember(char operation):
  operation_(operation),
  type_(Type::Operation)
{

}

potapova::ArithmExpMember& potapova::ArithmExpMember::operator=(long long num)
{
  type_ = Type::Num;
  num_ = num;
  return *this;
}

potapova::ArithmExpMember& potapova::ArithmExpMember::operator=(char operation)
{
  type_ = Type::Operation;
  operation_ = operation;
  return *this;
}

long long potapova::ArithmExpMember::getNum()
{
  return num_;
}

char potapova::ArithmExpMember::getOperation()
{
  return operation_;
}

potapova::ArithmExpMember::Type potapova::ArithmExpMember::getType()
{
  return type_;
}
