#ifndef FORWARDLISTITERATOR
#define FORWARDLISTITERATOR

#include <memory>
#include <list.hpp>

namespace hrushchev
{
  template< typename T >
  class ForwardList;

  template< typename T >
  class ForwardListConstIterator;

  template< typename T >
  class ForwardListIterator
  {
  friend class ForwardList< T >;
  friend class ForwardListConstIterator< T >;
  public:
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;
    using iterator_category = std::forward_iterator_tag;
    ForwardListIterator();
    ~ForwardListIterator() = default;
    explicit ForwardListIterator(details::List< T >* rhs);
    ForwardListIterator< T >& operator++();
    ForwardListIterator< T > operator++(int);
    T& operator*();
    T* operator->();
    bool operator==(const ForwardListIterator< T >& rhs) const;
    bool operator!=(const ForwardListIterator< T >& rhs) const;
    ForwardListIterator(const ForwardListConstIterator< T >& other) noexcept;
  private:
    details::List< T >* ptr_;
  };

  template< typename T >
  ForwardListIterator< T >::ForwardListIterator():
    ptr_(nullptr)
  {
  }

  template< typename T >
  ForwardListIterator< T >::ForwardListIterator(details::List< T >* rhs):
    ptr_(rhs)
  {
  }

  template< typename T >
  ForwardListIterator< T >& ForwardListIterator< T >::operator++()
  {
    if (ptr_)
    {
      ptr_ = ptr_->next_;
    }
    return *this;
  }

  template< typename T >
  ForwardListIterator< T > ForwardListIterator< T >::operator++(int)
  {
    ForwardListIterator< T > temp(*this);
    if (ptr_)
    {
      ptr_ = ptr_->next_;
    }
    return temp;
  }

  template< typename T >
  T& ForwardListIterator< T >::operator*()
  {
    return ptr_->data_;
  }

  template< typename T >
  T* ForwardListIterator< T >::operator->()
  {
    return std::addressof(ptr_->data_);
  }

  template < typename T >
  bool ForwardListIterator< T >::operator==(const ForwardListIterator< T >& rhs) const
  {
    return ptr_ == rhs.ptr_;
  }

  template< typename T >
  bool ForwardListIterator< T >::operator!=(const ForwardListIterator< T >& rhs) const
  {
    return ptr_ != rhs.ptr_;
  }

  template< typename T >
  ForwardListIterator< T >::ForwardListIterator(const ForwardListConstIterator< T >& other) noexcept:
    ptr_(const_cast< details::List< T > * >(other.ptr_))
  {
  }
}

#endif
