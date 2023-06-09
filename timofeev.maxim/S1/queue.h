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
    const T& drop() const;
    void push(const T  & rhs);
    void pop();
    bool isEmpty() const;

  private:
    List< T >* tail_;
    List< T >* head_;
  };
}
#endif
template <typename T>
timofeev::Queue<T>::Queue():
  tail_(nullptr),
  head_(nullptr)
{}
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
}

template <typename T>
bool timofeev::Queue<T>::isEmpty() const
{
  return head_ == nullptr;
}

template <typename T>
T& timofeev::Queue<T>::drop()
{
  if (isEmpty())
  {
    throw std::underflow_error("No value in queue");
  }
  return head_->data;
}

template <typename T>
void timofeev::Queue<T>::pop()
{
  if (isEmpty())
  {
    throw std::underflow_error("No value in queue");
  }

  else if (tail_ == head_)
  {
    delete tail_;
    tail_ = head_ = nullptr;
  }
  else
  {
    List<T>* temp = head_->next;
    delete head_;
    head_ = temp;
  }
}
template <typename T>
void timofeev::Queue<T>::push(const T& rhs)
{
  List<T>* newNode = new List<T>{rhs, nullptr};
  if (isEmpty())
  {
    head_ = tail_ = newNode;
  }
  else
  {
    tail_->next = newNode;
    tail_ = newNode;
  }
}
template <typename T>
const T& timofeev::Queue<T>::drop() const
{
  if (isEmpty())
  {
    throw std::underflow_error("No value in queue");
  }
  return head_->data;
}
