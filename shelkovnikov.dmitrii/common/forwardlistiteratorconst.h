#ifndef SPBSPU_LABS_2023_AADS_904_A_FORWARDLISTITERATORCONST_H
#define SPBSPU_LABS_2023_AADS_904_A_FORWARDLISTITERATORCONST_H
#include <iterator>
#include "nodeforwardlist.h"
namespace dimkashelk
{
  template< typename T >
  class ForwardList;
  template< typename T >
  class ForwardListIteratorConst: public std::iterator< std::input_iterator_tag, const T >
  {
  friend class ForwardList< T >;
  public:
    ForwardListIteratorConst &operator++()
    {
      ptr_ = ptr_->next;
      return *this;
    }
    ForwardListIteratorConst &operator++(int)
    {
      ptr_ = ptr_->next;
      return *this;
    }
    ForwardListIteratorConst &operator--()
    {
      ptr_ = ptr_->prev;
      return *this;
    }
    ForwardListIteratorConst &operator--(int)
    {
      ptr_ = ptr_->prev;
      return *this;
    }
    const T &operator*() const
    {
      return ptr_->data;
    }
    const T &operator->() const
    {
      return ptr_->data;
    }
    bool operator==(const ForwardListIteratorConst &other) const
    {
      return ptr_ == other.ptr_;
    }
    bool operator!=(const ForwardListIteratorConst &other) const
    {
      return ptr_ != other.ptr_;
    }
  private:
    details::NodeForwardList< T > *ptr_;
    explicit ForwardListIteratorConst(details::NodeForwardList< T > *ptr):
      ptr_(ptr)
    {}
  };
}
#endif
