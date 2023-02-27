#ifndef QUEUE_H
#define QUEUE_H
template< typename T >
class Queue {
public:
  Queue();
  ~Queue();
  void push(T rhs);
  T drop();
private:
  T *head;
  size_t size_;
};

template < typename T >
T Queue< T >::drop()
{
  return nullptr;
}

template < typename T >
Queue< T >::Queue():
  head(new T),
  size_(0)
{
}

template < typename T >
Queue< T >::~Queue()
{
}
#endif
