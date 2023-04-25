#ifndef LISTFORUNIQUEPTR_H
#define LISTFORUNIQUEPTR_H

#include "list.h"
#include "mathExprPtr.h"

template<>
struct List< MathExprPtr >
{
  MathExprPtr data;
  List< MathExprPtr >* otherList;

  List(MathExprPtr& data, List< MathExprPtr >* otherList = nullptr);
};

List< MathExprPtr >::List(MathExprPtr& data, List< MathExprPtr >* otherList) :
  data(std::move(data)),
  otherList(otherList)
{

}

#endif
