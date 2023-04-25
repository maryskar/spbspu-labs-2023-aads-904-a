#ifndef FORWARDLIST_H
#define FORWARDLIST_H
#include "common/listnode.h"
#include <iostream>
#include <forward_list>
template < typename T >
class ForwardList
{
public:
  using f_list_t = ForwardList < T >;
  ForwardList();
  ~ForwardList() = default;
  explicit ForwardList(const T &value);
  explicit ForwardList(size_t count);
  ForwardList(const ForwardList &other);
  ForwardList(ForwardList &&other);
  ForwardList(std::initializer_list < T > init);
  bool isEmpty() const;
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
  details::ListNode < T > *node_;
};
template < typename T >
bool ForwardList < T >::isEmpty() const
{
  return node_ == nullptr;
}
template < typename T >
ForwardList < T >::ForwardList(const T &value):
  node_(nullptr)
{
  if (value.isEmpty())
  {
    node_ = nullptr;
  }
  else
  {
    details::ListNode < T > *tmp = value.node_;
    while (tmp != nullptr)
    {
      auto rhs = tmp->data_;
      if (node_ == nullptr)
      {
        node_ = new details::ListNode< T >{rhs, nullptr};
      }
      else
      {
        node_->next_ = new details::ListNode< T >{rhs, nullptr};
        node_ = node_->next_;
      }
      tmp = tmp->next_;
    }
  }
}
template < typename T >
ForwardList < T >::ForwardList():
  node_(nullptr)
{
}
template < typename T >
void ForwardList < T >::reverse() noexcept
{
  std::forward_list < int > numbers{1, 2, 3, 4, 5, 6, 7};
}
#endif
