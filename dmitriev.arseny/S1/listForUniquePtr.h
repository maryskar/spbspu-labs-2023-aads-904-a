#ifndef LISTFORU_H
#define LISTFORU_H

#include "list.h"
#include "mathExprPtr.h"

template<>
struct List< MathExprPtr >
{
  MathExprPtr data;
  List< MathExprPtr >* otherList;

  List(MathExprPtr& data, List< MathExprPtr >* otherList = nullptr);
  ~List();
};

List< MathExprPtr >::List(MathExprPtr& data, List< MathExprPtr >* otherList) :
  data(std::move(data)),
  otherList(otherList)
{

}

List< MathExprPtr >::~List()
{

}

#endif
