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
  Node< T >* head;

};

template< typename T >
ForwardList< T >::ForwardList():
  head(nullptr)
{}

template< typename T >
ForwardList< T >::~ForwardList()
{
  clear(head);
}

template< typename T >
void ForwardList< T >::push_front(const T& data)
{
  Node< T >* newHead = new Node< T >{data, head};
  head = newHead;
}

template< typename T >
void ForwardList< T >::push_front(T&& data)
{
  Node< T >* newHead = new Node< T >{std::move(data), head};
  head = newHead;
}

template< typename T >
const T& ForwardList< T >::front() const
{
  return head->data;
}

template< typename T >
T& ForwardList< T >::front()
{
  return head->data;
}

template< typename T >
void ForwardList< T >::pop_front()
{
  Node< T >* newHead = head->next;
  delete head;
  head = newHead;
}

#endif
