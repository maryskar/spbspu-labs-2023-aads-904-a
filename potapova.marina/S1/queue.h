#ifndef QUEUE_H
#define QUEUE_H

template< typename T >
class Queue
{
  public:
    Queue();
    ~Queue() {}
    void push(const T& elem);
    T drop();
  private:
    struct Node
    {
      T* data;
    };
};
 

#endif
