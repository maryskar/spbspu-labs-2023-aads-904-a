#ifndef QUEUE_H
#define QUEUE_H
#include "node.h"
template< typename T >
class Queue
{
public:
  Queue();
  void push(T rhs);
  T drop();
  ~Queue();
private:
  Node< T >* head;
};

template< typename T >
Queue< T >::Queue():
	begin_(nullptr)
{}

template< typename T >
void Queue< T >::push(T rhs)
{
  Node* temp = new Node;
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
#endif
