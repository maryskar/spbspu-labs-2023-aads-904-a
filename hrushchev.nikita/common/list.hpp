#ifndef LIST_HPP
#define LIST_HPP

#include <utility>
namespace details
{
  template< typename T >
  struct List
  {
    T data_;
    List< T >* next_;
    List();
    List(const T& value);
    List(T&& value);
  };

  template< typename T >
  List< T >::List():
    data_(),
    next_(nullptr)
  {
  }

  template< typename T >
  List< T >::List(const T& value):
    data_(value),
    next_(nullptr)
  {
  }

  template< typename T >
  List< T >::List(T&& value):
    data_(std::move(value)),
    next_(nullptr)
  {
  }
}
#endif
