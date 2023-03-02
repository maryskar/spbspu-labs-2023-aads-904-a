#ifndef QUEUE_H
#define QUEUE_H
#include "node.h"
#include "stack.h"
template < typename T >
class Queue
{
public:
  Queue();
  ~Queue();
  void push(T rhs);
  T pop();
  void splitLine(const std::string &string);
  void parseQueue();
private:
  Node< T > *head_;
  Node< T > *tail_;
  size_t size_;
  bool isOperator(char c)
  {
    return (c == '+' || c == '-' || c == '*' || c == '/');
  }
  bool operationStackPopCondition(char q, char s)
  {
    return (q != '+' && q != '-') || (s != '*' && s != '/');
  }
};
template < typename T >
T Queue< T >::pop()
{
  T el = head_->data_;
  Node< T > *subHead = head_->next_;
  delete head_;
  head_ = subHead;
  return el;
}
template < typename T >
Queue< T >::Queue():
  head_(nullptr),
  tail_(nullptr),
  size_(0)
{
}
template < typename T >
Queue< T >::~Queue()
{
}
template < typename T >
void Queue< T >::splitLine(const std::string &string)
{
  for (char c: string)
  {
    if (c != ' ')
    {
      push(c);
    }
  }
}
template < typename T >
void Queue< T >::parseQueue()
{
  Stack<char> *stack = new Stack<char>;
  while (head_->next_ != nullptr)
  {
    T qEl = pop();
    T sEl = '_';
    if (!stack->isEmpty()) sEl = stack->top_->data_;
    //std::cout << qEl << " " << sEl << "\n";

    if (qEl == '(')
    {
      stack->push(qEl);
    }
    else if (qEl == ')')
    {
      //вытащить все из стека до открывающей
      while (sEl != '(')
      {
        sEl = stack->top_->data_;
        std::cout << sEl << " ";
        stack->pop();
      }
      pop();
      stack->pop();
      sEl = stack->top_->data_;
    }
    else if (std::isdigit(static_cast<unsigned char>(qEl)))
    {
      std::cout << qEl << " ";
    }
    else if (isOperator(qEl))
    {
      while (isOperator(sEl) && operationStackPopCondition(qEl, sEl))
      {
        sEl = stack->top_->data_;
        std::cout << sEl << " ";
        stack->pop();
      }
      stack->push(qEl);
    }
  }
}
template < typename T >
void Queue< T >::push(T rhs)
{
  if (head_ == nullptr)
  {
    head_ = new Node< T >{rhs, nullptr};
    tail_ = head_;
  }
  else
  {
    tail_->next_ = new Node< T >{rhs, nullptr};
    tail_ = tail_->next_;
  }
}
#endif
