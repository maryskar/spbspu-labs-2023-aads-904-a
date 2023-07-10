#ifndef FORWARDLSIT_H
#define FORWARDLSIT_H

#include "node.h"

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
  Node< T >* fakeNode;
//  size_t size;

};

template< typename T >
ForwardList< T >::ForwardList():
  fakeNode(new Node< T >{T(), nullptr})
{}

template< typename T >
ForwardList< T >::~ForwardList()
{
  clear(fakeNode->next);
}

template< typename T >
void ForwardList< T >::push_front(const T& data)
{
  Node< T >* newHead = new Node< T >{data, fakeNode->next};
  fakeNode->next = newHead;
}

template< typename T >
void ForwardList< T >::push_front(T&& data)
{
  Node< T >* newHead = new Node< T >{std::move(data), fakeNode->next};
  fakeNode->next = newHead;
}

template< typename T >
const T& ForwardList< T >::front() const
{
  return fakeNode->next->data;
}

template< typename T >
T& ForwardList< T >::front()
{
  return fakeNode->next->data;
}

template< typename T >
void ForwardList< T >::pop_front()
{
  Node< T >* newHead = fakeNode->next->next;
  delete fakeNode->next;

  fakeNode->next = newHead;
}

#endif
