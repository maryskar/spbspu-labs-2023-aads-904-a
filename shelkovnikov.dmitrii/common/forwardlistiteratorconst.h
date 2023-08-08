#ifndef SPBSPU_LABS_2023_AADS_904_A_FORWARDLISTITERATORCONST_H
#define SPBSPU_LABS_2023_AADS_904_A_FORWARDLISTITERATORCONST_H
#include <iterator>
#include "nodeOneWayList.h"
namespace dimkashelk
{
  template< typename T >
  class ForwardList;
  template< typename T >
  class ForwardListIterator;
  template< typename T >
  class ForwardListIteratorConst: public std::iterator< std::forward_iterator_tag, const T >
  {
  friend class ForwardListIterator< T >;
  friend class ForwardList< T >;
  public:
    ForwardListIteratorConst(const ForwardListIterator< T > &it):
      ptr_(it.ptr_)
    {}
    ForwardListIteratorConst &operator++()
    {
      ptr_ = ptr_->next;
      return *this;
    }
    ForwardListIteratorConst operator++(int)
    {
      ForwardListIteratorConst< T > result(*this);
      ++(*this);
      return result;
    }
    const T &operator*() const
    {
      return ptr_->data;
    }
    const T *operator->() const
    {
      return std::addressof(ptr_->data);
    }
    bool operator==(const ForwardListIteratorConst &other) const
    {
      return ptr_ == other.ptr_;
    }
    bool operator!=(const ForwardListIteratorConst &other) const
    {
      return !(ptr_ == other.ptr_);
    }
  private:
    details::NodeOneWayList< T > *ptr_;
    explicit ForwardListIteratorConst(details::NodeOneWayList< T > *ptr):
      ptr_(ptr)
    {}
  };
}
#endif
