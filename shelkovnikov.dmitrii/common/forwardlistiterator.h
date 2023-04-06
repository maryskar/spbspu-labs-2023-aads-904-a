#ifndef SPBSPU_LABS_2023_AADS_904_A_FORWARDLISTITERATOR_H
#define SPBSPU_LABS_2023_AADS_904_A_FORWARDLISTITERATOR_H
#include <iterator>
#include "nodeforwardlist.h"
#include "forwardlist.h"
namespace dimkashelk
{
  template< typename T >
  class ForwardList;
  template< typename T >
  class Iterator: public std::iterator< std::input_iterator_tag, T >
  {
  friend class ForwardList< T >;
  public:
    Iterator &operator++()
    {
      ptr_ = ptr_->next;
      return *this;
    }
    Iterator &operator++(int)
    {
      ptr_ = ptr_->next;
      return *this;
    }
    Iterator &operator--()
    {
      ptr_ = ptr_->prev;
      return *this;
    }
    Iterator &operator--(int)
    {
      ptr_ = ptr_->prev;
      return *this;
    }
    T &operator*()
    {
      return ptr_->data;
    }
    const T &operator*() const
    {
      return ptr_->data;
    }
    bool operator==(const Iterator< T > &other) const
    {
      return ptr_ == other.ptr_;
    }
    bool operator!=(const Iterator &other) const
    {
      return ptr_ != other.ptr_;
    }
  private:
    details::Node< T > *ptr_;
    explicit Iterator(details::Node< T > *ptr):
      ptr_(ptr)
    {}
  };
}
#endif
