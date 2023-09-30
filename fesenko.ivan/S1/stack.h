#ifndef STACK_H
#define STACK_H
#include <stdexcept>
#include <utility>
#include <memory>
#include <dictionary/forward-list/list.h>
namespace fesenko
{
  template< typename T >
  class Stack
  {
   public:
    Stack();
    Stack(const Stack< T > &);
    Stack(Stack< T > &&);
    Stack< T > &operator=(const Stack< T > &);
    Stack< T > &operator=(Stack< T > &&);
    ~Stack();
    void push(const T &);
    void push(T &&);
    T &top();
    const T &top() const;
    void pop();
    bool isEmpty() const noexcept;
   private:
    List< T > *head_;
    void copy(const Stack< T > &);
  };
}

template< typename T >
fesenko::Stack< T >::Stack():
  head_(nullptr)
{}

template< typename T >
fesenko::Stack< T >::Stack(const Stack< T > &other):
  Stack()
{
  copy(other);
}

template< typename T >
fesenko::Stack< T >::Stack(Stack< T > &&other):
  head_(std::move(other.head_))
{}

template< typename T >
fesenko::Stack< T > &fesenko::Stack< T >::operator=(const Stack< T > &other)
{
  if (this != std::addressof(other))
  {
    copy(other);
  }
  return *this;
}

template< typename T >
fesenko::Stack< T > &fesenko::Stack< T >::operator=(Stack< T > &&other)
{
  if (this != std::addressof(other))
  {
    head_ = std::move(other.head_);
  }
  return *this;
}

template< typename T >
fesenko::Stack< T >::~Stack()
{
  deleteList(head_);
}

template< typename T >
void fesenko::Stack< T >::push(const T &rhs)
{
  List< T > *temp = new List< T >{rhs, head_};
  head_ = temp;
}

template< typename T >
void fesenko::Stack< T >::push(T &&rhs)
{
  List< T > *temp = new List< T >{std::move(rhs), head_};
  head_ = temp;
}

template< typename T >
const T &fesenko::Stack< T >::top() const
{
  if (isEmpty()) {
    throw std::out_of_range("Stack is empty");
  }
  return head_->data;
}

template< typename T >
T &fesenko::Stack< T >::top()
{
  return const_cast< T & >((static_cast< const Stack< T > & >(*this)).top());
}

template< typename T >
void fesenko::Stack< T >::pop()
{
  if (isEmpty()) {
    throw std::out_of_range("Stack is empty");
  }
  List< T > *temp = head_->next;
  delete head_;
  head_ = temp;
}

template< typename T >
bool fesenko::Stack< T >::isEmpty() const noexcept
{
  return head_ == nullptr;
}

template< typename T >
void fesenko::Stack< T >::copy(const Stack< T > &other)
{
  auto res = copyList(other.head_);
  head_ = res.first;
}
#endif
