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
template <typename T>
timofeev::Queue<T>::Queue():
  tail_(nullptr),
  head_(nullptr),
  sizeQ_(0)
{}
template <typename T>
int timofeev::Queue<T>::getSize()
{
  return sizeQ_;
}
template <typename T>
timofeev::Queue<T>::~Queue()
{
  if (tail_ == head_)
  {
    delete tail_;
    tail_ = head_ = nullptr;
  }
  else
  {
    while (!isEmpty() && head_->next != nullptr)
    {
      List< T >* tempHead = head_;
      head_ = head_->next;
      delete tempHead;
    }
  }
  sizeQ_ = 0;
}