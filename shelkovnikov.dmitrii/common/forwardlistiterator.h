#ifndef SPBSPU_LABS_2023_AADS_904_A_FORWARDLISTITERATOR_H
#define SPBSPU_LABS_2023_AADS_904_A_FORWARDLISTITERATOR_H
#include <iterator>
#include "nodeforwardlist.h"
#include "forwardlistiteratorconst.h"
namespace dimkashelk
{
  template< typename T >
  class ForwardList;
  template< typename T >
  class ForwardListIteratorConst;
  template< typename T >
  class ForwardListIterator: public std::iterator< std::input_iterator_tag, T >
  {
  friend class ForwardList< T >;
  friend class ForwardListIteratorConst< T >;
  public:
    ForwardListIterator &operator++()
    {
      ptr_ = ptr_->next;
      return *this;
    }
    ForwardListIterator &operator++(int)
    {
      ptr_ = ptr_->next;
      return *this;
    }
    T &operator*() const
    {
      return ptr_->data;
    }
    T &operator->() const
    {
      return ptr_->data;
    }
    bool operator==(const ForwardListIterator &other) const
    {
      return ptr_ == other.ptr_;
    }
    bool operator!=(const ForwardListIterator &other) const
    {
      return ptr_ != other.ptr_;
    }
  private:
    details::NodeForwardList< T > *ptr_;
    explicit ForwardListIterator(details::NodeForwardList< T > *ptr):
      ptr_(ptr)
    {}
  };
}
#endif
