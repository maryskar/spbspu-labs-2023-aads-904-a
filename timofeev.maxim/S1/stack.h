#ifndef STACK_H
#define STACK_H
#include <stdexcept>
#include "List.h"
namespace timofeev
{
  template <typename T>
  class Stack
  {
  public:
    explicit Stack();
    ~Stack();
    void push(const T& rhs);
    void pop();
    T& drop();
    const T& drop() const;
    bool isEmpty() const;
  private:
    List< T >* top_;
  };
}
template <typename T>
timofeev::Stack<T>::Stack():
        top_(nullptr)
{}
template <typename T>
bool timofeev::Stack<T>::isEmpty() const
{
  return top_ == nullptr;
}
template <typename T>
timofeev::Stack<T>::~Stack()
{
  while (!isEmpty())
  {
    List<T>* temp = top_;
    top_ = top_->next;
    delete temp;
  }
  template <typename T>
  void timofeev::Stack<T>::pop()
  {
    if (isEmpty())
    {
      throw std::runtime_error("Stack is empty1");
    }
    else if (!top_->next)
    {
      delete top_;
      top_ = nullptr;
    }
    else
    {
      List<T>* temp = top_;
      top_ = temp->next;
      delete temp;
    }
  }

}

#endif
