#ifndef QUEUE_H
#define QUEUE_H
#include <stdexcept>
#include "List.h"
namespace timofeev
{
  template <typename T>
  class Queue
  {
  public:
    explicit Queue();
    ~Queue();

    T& drop();
    int getSize();
    void push(const T  & rhs);
    void pop();
    bool isEmpty() const;

  private:
    int sizeQ_;
    List< T >* tail_;
    List< T >* head_;
  };
}
#endif
