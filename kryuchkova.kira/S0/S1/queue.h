#ifndef QUEUE_H
#define QUEUE_H

template< typename T >
class Queue
{
  public:
    Queue();
    Queue(const Queue< T > &queue);
    ~Queue();
    void push(T rhs);
    T drop();
    bool isEmpty();
  private:
    Node< T > *head_;
    Node< T > *tail_;
};

template< typename T >
Queue< T >::Queue():
  head_(nullptr),
  tail_(nullptr)
{}

template< typename T >
Queue< T >::Queue(const Queue< T > &queue):
  head_(nullptr),
  tail_(nullptr)
{
  Node< T > *first = queue.head_;
  while (first)
  {
    push(first->data);
    first = first->next_;
  }
}

template< typename T >
Queue< T >::~Queue()
{
  while (head_)
  {
    drop();
  }
}

template< typename T >
void Queue< T >::push(T rhs)
{
  
}

#endif
