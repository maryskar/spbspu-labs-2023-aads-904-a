#ifndef STACK_H
#define STACK_H
#include <stdexcept>
#include "../common/List.h"
namespace timofeev
{
  template < typename T >
  class Stack
  {
  public:
    Stack();
    ~Stack();
    void push(const T& rhs);
    void pop();
    T& get();
    const T& get() const;
    bool isEmpty() const;
  private:
    List< T >* top_;
  };
}
template < typename T >
timofeev::Stack< T >::Stack():
  top_(nullptr)
{}
template < typename T >
bool timofeev::Stack< T >::isEmpty() const
{
  return top_ == nullptr;
}
template < typename T >
timofeev::Stack< T >::~Stack()
{
  clearlist(top_);
}
template < typename T >
void timofeev::Stack< T >::pop()
{
  if (isEmpty())
  {
    throw std::runtime_error("Stack is empty");
  }
  else
  {
    List< T >* temp = top_;
    top_ = temp->next;
    delete temp;
  }
}
template < typename T >
void timofeev::Stack< T >::push(const T& rhs)
{
  List< T >* newTop = new List< T >;
  newTop->data = rhs;
  newTop->next = top_;
  top_ = newTop;
}
template < typename T >
T& timofeev::Stack< T >::get()
{
  if (isEmpty())
  {
    throw std::runtime_error("Stack is empty");
  }
  return top_->data;
}
template < typename T >
const T& timofeev::Stack< T >::get() const
{
  if (isEmpty())
  {
    throw std::runtime_error("Stack is empty");
  }
  return top_->data;
}
#endif
