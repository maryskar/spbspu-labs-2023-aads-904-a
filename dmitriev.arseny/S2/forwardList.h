#ifndef FORWARDLSIT_H
#define FORWARDLSIT_H

#include "forwardIterator.h"

namespace dmitriev
{
  template< typename T >
  class ForwardList
  {
  public:
    ForwardList();
    ~ForwardList();

    void push_front(const T& data);
    void push_front(T&& data);

    const T& front() const;
    T& front();

    void pop_front();

  private:
    dmitriev::List< T >* fakeNode;
    //  size_t size;

  };
}

template< typename T >
dmitriev::ForwardList< T >::ForwardList():
  fakeNode(new dmitriev::List< T >{T(), nullptr})
{}

template< typename T >
dmitriev::ForwardList< T >::~ForwardList()
{
  clear(fakeNode->otherList);
}

template< typename T >
void dmitriev::ForwardList< T >::push_front(const T& data)
{
  dmitriev::List< T >* newHead = new dmitriev::List< T >{data, fakeNode->next};
  fakeNode->next = newHead;
}

template< typename T >
void dmitriev::ForwardList< T >::push_front(T&& data)
{
  dmitriev::List< T >* newHead = new dmitriev::List< T >{std::move(data), fakeNode->otherList};
  fakeNode->otherList = newHead;
}

template< typename T >
const T& dmitriev::ForwardList< T >::front() const
{
  return fakeNode->next->data;
}

template< typename T >
T& dmitriev::ForwardList< T >::front()
{
  return fakeNode->otherList->data;
}

template< typename T >
void dmitriev::ForwardList< T >::pop_front()
{
  dmitriev::List< T >* newHead = fakeNode->next->next;
  delete fakeNode->next;

  fakeNode->next = newHead;
}

#endif
