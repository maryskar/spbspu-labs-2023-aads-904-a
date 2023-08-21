#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H
#include <iterator>
#include <initializer_list>
#include "forward_list_const_iterator.h"
#include "forward_list_iterator.h"
#include "../common/node.h"

namespace kryuchkova
{
  template< typename T >
  class ForwardList
  {
  public:
    using iterator = ForwardIterator< T >;
    using const_iterator = ConstForwardIterator< T >;
    using this_t = ForwardList< T >;
    ForwardList();
    ForwardList(const this_t & rhs);
    ForwardList(this_t && rhs);
    ForwardList(std::initializer_list< T > init);
    ~ForwardList();

    this_t & operator=(const this_t & fwdlst);
    this_t & operator=(this_t && fwdlst);
    this_t & operator=(std::initializer_list< T > init);

    iterator insert_after(const_iterator pos, const T & val);
    iterator insert_after(const_iterator pos, T && val);
    iterator insert_after(const_iterator pos, std::size_t n, const T & val);
    iterator erase_after(const_iterator pos);
    iterator erase_after(const_iterator first, const_iterator last);

    iterator before_begin() noexcept;
    const_iterator before_begin() const noexcept;
    const_iterator cbefore_begin() const noexcept;
    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;
    iterator last() noexcept;
    const_iterator last() const noexcept;
    const_iterator clast() const noexcept;

    bool IsEmpty() const noexcept;
    void clear() noexcept;
    void push_front(const T & val);
    void push_front(T && val);
    void pop_front() noexcept;
    void resize(std::size_t count);
    void resize(std::size_t count, const T & val);
    void swap(this_t & other) noexcept;
    void splice_after(const_iterator pos, this_t & other);
    void splice_after(const_iterator pos, this_t && other);
    void splice_after(const_iterator pos, this_t & other, const_iterator iter);
    void splice_after(const_iterator pos, this_t && other, const_iterator iter);
    void splice_after(const_iterator pos, this_t & other, const_iterator first, const_iterator last);
    void splice_after(const_iterator pos, this_t && other, const_iterator first, const_iterator last);
    void remove(const T & val);
    void reverse() noexcept;

  private:
    iterator fake_;
    iterator last_;
  };

  template < typename T >
  ForwardList< T >::ForwardList():
    fake_(static_cast< Node< T > * >(::operator new (sizeof(Node< T >)))),
    last_(iterator(nullptr))
  {
    fake_.node_->next_ = nullptr;
  }

  template < typename T >
  bool ForwardList< T >::IsEmpty() const noexcept
  {
    return fake_.node_->next_ == nullptr;
  }

  template < typename T >
  void ForwardList< T >::clear() noexcept
  {
    if (IsEmpty())
    {
      return;
    }
    while (fake_.node_->next_ != nullptr)
    {
      Node< T > * temp = fake_.node_->next_;
      fake_.node_->next_ = temp->next_;
      delete temp;
    }
    fake_.node_->next_ = nullptr;
    last_.node_ = nullptr;
  }

  template < typename T >
  ForwardList< T >::~ForwardList()
  {
    clear();
    ::operator delete(fake_.node_);
  }

  template< typename T >
  ForwardList< T >::ForwardList(const this_t & rhs):
   ForwardList(rhs.begin(), rhs.end())
  {}

  template< typename T >
  ForwardList< T >::ForwardList(this_t && rhs):
   ForwardList()
  {
    swap(rhs);
  }

  template< typename T >
  ForwardList< T >::ForwardList(std::initializer_list< T > init):
   ForwardList(init.begin(), init.end())
  {}


  template< typename T >
  ForwardList< T > & ForwardList< T >::operator=(const this_t & fwdlst)
  {
    if (this == std::addressof(fwdlst))
    {
      return *this;
    }
    this_t temp(fwdlst);
    clear();
    swap(temp);
    return *this;
  }

  template< typename T >
  ForwardList< T > & ForwardList< T >::operator=(this_t && fwdlst)
  {
    if (this == std::addressof(fwdlst))
    {
      return *this;
    }
    clear();
    swap(fwdlst);
    return *this;
  }

  template< typename T >
  ForwardList< T > & ForwardList< T >::operator=(std::initializer_list< T > init)
  {
    this_t temp(init);
    clear();
    swap(temp);
    return *this;
  }

  template< typename T >
  ForwardIterator< T > ForwardList< T >::before_begin() noexcept
  {
    return fake_;
  }

  template< typename T >
  ConstForwardIterator< T > ForwardList< T >::before_begin() const noexcept
  {
    return cbefore_begin();
  }

  template< typename T >
  ConstForwardIterator< T > ForwardList< T >::cbefore_begin() const noexcept
  {
    return const_iterator(fake_);
  }

  template< typename T >
  ForwardIterator< T > ForwardList< T >::begin() noexcept
  {
    return iterator(fake_.node_->next);
  }

  template< typename T >
  ConstForwardIterator< T > ForwardList< T >::begin() const noexcept
  {
    return cbegin();
  }

  template< typename T >
  ConstForwardIterator< T > ForwardList< T >::cbegin() const noexcept
  {
    return const_iterator(fake_.node_->next);
  }

  template< typename T >
  ForwardIterator< T > ForwardList< T >::end() noexcept
  {
    return fake_;
  }

  template< typename T >
  ConstForwardIterator< T > ForwardList< T >::end() const noexcept
  {
    return cend();
  }

  template< typename T >
  ConstForwardIterator< T > ForwardList< T >::cend() const noexcept
  {
    return const_iterator(fake_);
  }

  template< typename T >
  ForwardIterator< T > ForwardList< T >::last() noexcept
  {
    return last_;
  }

  template< typename T >
  ConstForwardIterator< T > ForwardList< T >::last() const noexcept
  {
    return clast();
  }

  template< typename T >
  ConstForwardIterator< T > ForwardList< T >::clast() const noexcept
  {
    return const_iterator(last_);
  }


}

#endif
