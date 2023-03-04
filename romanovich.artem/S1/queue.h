#ifndef QUEUE_H
#define QUEUE_H
#include "node.h"
#include "stack.h"
#include <iostream>
#include <algorithm>
template < typename T >
class Queue
{
public:
  Queue();
  ~Queue();
  void push(T rhs);
  T pop();
  void splitLine(const std::string &string);
  void parseQueue(Queue< T > *postfixQueue);
  bool isEmpty()
  {
    return size_ == 0;
  }
  void print()
  {
    Node< T > *e = head_;
    while (e != nullptr)
    {
      std::cout << e->data_;
      e = e->next_;
    }
    std::cout << "\n";
  }
private:
  Node< T > *head_;
  Node< T > *tail_;
  size_t size_;
  bool isOperator(const std::string& c)
  {
    return (c == "+" || c == "-" || c == "*" || c == "/" || c == "%");
  }
  bool operationStackPopCondition(const std::string& q, const std::string& s)
  {
    return ((q == "+" || q == "-") && (s == "*" || s == "/" || s == "%"));
  }
};
template < typename T >
T Queue< T >::pop()
{
  T el = head_->data_;
  Node< T > *subHead = head_->next_;
  delete head_;
  head_ = subHead;
  size_--;
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
  int begin = 0;
  int end = string.find(' ');
  while (end != -1)
  {
    push(string.substr(begin, end - begin));
    begin = end + 1;
    end = string.find(' ', begin);
  }
  push(string.substr(begin, end - begin));
}
template < typename T >
void Queue< T >::parseQueue(Queue< T > *postfixQueue)
{
  Stack< T > *stack = new Stack< T >;
  while (!isEmpty() or !stack->isEmpty())
  {
    if (!isEmpty())
    {
      T qEl = pop();
      if (qEl == "(")
      {
        stack->push(qEl);
      }
      if (qEl == ")")
      {
        while (stack->top_->data_ != "(")
        {
          postfixQueue->push(stack->pop());
          if (stack->isEmpty())
          {
            break;
          }
        }
        stack->pop();
      }
      if (std::all_of(qEl.begin(), qEl.end(), ::isdigit))
      {
        postfixQueue->push(qEl);
      }
      if (isOperator(qEl))
      {
        if (!stack->isEmpty())
        {
          if (operationStackPopCondition(qEl, stack->top_->data_))
          {
            postfixQueue->push(stack->pop());
          }
        }
        stack->push(qEl);
      }
    }
    else
    {
      while (!stack->isEmpty())
      {
        postfixQueue->push(stack->pop());
      }
    }
    std::cout << "queue: ";
    print();
    std::cout << "stack: ";
    stack->print();
      std::cout << "result: "; postfixQueue->print();
    std::cout << "\n";
  }
  delete stack;
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
  size_++;
}
#endif
