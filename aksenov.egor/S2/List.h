#ifndef LIST_H
#define LIST_H
#include <utility>

namespace aksenov
{
  template< typename T >
  struct listT
  {
    T data;
    listT< T > *next;
    listT():
      data(),
      next(nullptr)
    {}

    listT(const T &val):
      data(val),
      next(nullptr)
    {}

    listT(const T &rhs, listT< T > *val):
      data(rhs),
      next(val)
    {
    }
  };

  template< class T >
  void free(listT< T > *head)
  {
    while (head)
    {
      auto todel = head;
      head = head->next;
      delete todel;
    }
  }

  template< typename T >
  std::pair< listT< T > *, listT< T > * > copyLst(listT< T > *head)
  {
    if (!head)
    {
      return {nullptr, nullptr};
    }
    listT< T > *newHead = new listT< T >(head->data);
    listT< T > *cur = newHead;
    listT< T > *origin = head->next;
    while (origin)
    {
      cur->next = new listT< T >(origin->data);
      cur = cur->next;
      origin = origin->next;
    }
    return {newHead, cur};
  }

}
#endif
