#ifndef QUEUE_H
#define QUEUE_H
#include "list.h"
template< typename T >
class Queue
{
public:
  Queue();
  Queue(const Queue& rhs);
  void push(T rhs);
  T drop();
  ~Queue();
private:
  List< T >* head_;
  List< T >* tail_;
};

template< typename T >
Queue< T >::Queue() :
	head_(nullptr),
	tail_(nullptr)
{}

template< typename T >
void Queue< T >::push(T rhs)
{
  Node< T >* temp = new List;
  temp->data = rhs;
  temp->next = nullptr;
  if (!head)
  {
	head = temp;
  }
  else
  {
	Node< T >* current = head;
	while (current->next)
	{
      current = current->next;
	}
	current->next = temp;
  }
}

template< typename T >
T Queue< T >::drop()
{
  if (head == nullptr)
  {
    throw std::out_of_range("Queue is empty");
  }
  Node< T >* newhead = head->next;
}
#endif
