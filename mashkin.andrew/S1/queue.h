#ifndef QUEUE_H
#define QUEUE_H
#include <cstddef>

template < typename T >
class Queue
{
  public:
    explicit Queue();
    void enqueue(T rhs);
    void dequeue();
    T drop();

  private:
    static const size_t OVERFLOW = 50;
    T* queue_[OVERFLOW];
    size_t head_;
    size_t tail_;
};
#endif
