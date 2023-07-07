#ifndef FORWARDLIST_HPP
#define FORWARDLIST_HPP

#include <cstddef>
#include <list.hpp>

template <typename T>
class ForwardList
{
  public:
    void pushFront(const T& value);
    List< T >* head_;
};

template <typename T>
void ForwardList< T >::pushFront(const T& value)
{
  List< T >* temp = new List< T >();
  temp->data_ = value;
  temp->next_ = head_;
  head_ = temp;
}
#endif
