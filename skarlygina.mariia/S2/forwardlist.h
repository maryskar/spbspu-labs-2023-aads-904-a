#ifndef FORWARDLIST_H
#define FORWARDLIST_H
#include "iterator.h"
#include "citerator.h"
#include "list.h"

namespace skarlygina
{
  template < typename T >
  class ForwardList
  {
  public:
    ForwardList();
    ForwardList(const ForwardList< T >&);
    ForwardList(ForwardList< T >&&) noexcept;
    ~ForwardList();

    Iterator< T > begin();
    Iterator< T > end();
    CIterator< T > begin() const;
    CIterator< T > end() const;
    CIterator< T > cbegin() const;
    CIterator< T > cend() const;

    bool isEmpty() const noexcept;
    size_t getSize() const;
    T front() const;
    T back() const;
    void clear();
    Iterator< T > insertAfter(CIterator< T >, const T&);
    Iterator< T > eraseAfter(CIterator< T >);
    void pushBack(const T&);
    void pushFront(const T&);
    void popFront();
    void popBack();

  private:
    List< T >* head_;
    List< T >* tail_;
  };

  template< typename T >
  ForwardList< T >::ForwardList():
    head_(nullptr),
    tail_(nullptr)
  {}

  template< typename T >
  ForwardList< T >::ForwardList(const ForwardList< T >& other):
    List< T >::List(other), 
    head_(nullptr),
    tail_(nullptr)
  {}

  template< typename T >
  ForwardList< T >::ForwardList(ForwardList< T >&& other) noexcept:
    List< T >::List(other)
  {}

  template< typename T >
  ForwardList< T >::~ForwardList()
  {
    List< T >::~List();
  }

  template < typename T >
  Iterator< T > ForwardList< T >::begin()
  {
    return Iterator< T >(cbegin());
  }
  template < typename T >
  Iterator< T > ForwardList< T >::end()
  {
    return Iterator< T >(cend());
  }

  template < typename T >
  CIterator< T > ForwardList< T >::begin() const
  {
    return CIterator< T >(cbegin());
  } 
  template < typename T >
  CIterator< T > ForwardList< T >::end() const
  {
    return CIterator< T >(cend());
  }

  template < typename T >
  CIterator< T > ForwardList< T >::cbegin() const
  {
    return CIterator< T >(head_);
  }
  template < typename T >
  CIterator< T > ForwardList< T >::cend() const
  {
    return ConstIterator< T >(nullptr);
  }


}

#endif

