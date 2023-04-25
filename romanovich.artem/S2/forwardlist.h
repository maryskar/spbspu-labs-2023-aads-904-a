#ifndef FORWARDLIST_H
#define FORWARDLIST_H
#include "common/listnode.h"
#include <iostream>
#include <forward_list>
template < typename T >
class ForwardList
{
public:
  using f_list_t = ForwardList<T>;
  ForwardList():
    node(nullptr)
  {
  }
  ~ForwardList() = default;
  ///ForwardList(const this_t &) = default;
  ///this_t & operator=(const this_t &) = default;

  ///this_t & operator++();
  ///this_t operator++(int);

  ///T & operator*();  //+ const-версия
  ///T * operator->(); //+ const-версия

  ///bool operator!=(const this_t &) const;
  ///bool operator==(const this_t &) const;

  void reverse() noexcept;
private:
  details::ListNode<T> *node;
};
template < typename T >
void ForwardList<T>::reverse() noexcept
{
  std::forward_list<int> numbers{1, 2, 3, 4, 5, 6, 7};
}
#endif
