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
    T el = pop();
    std::cout << el << " ";

    //std::cout << stack->top_->data_ << "\n";

    if (el == '(')
    {
      stack->push(el);
    }
    else if (el == ')')
    {
      //вытащить все из стека до открывающей
      //удалить два верхних элемента стека
    }
    else if (std::isdigit(static_cast<unsigned char>(el)))
    {
      //to result
    }
    else if (isOperator(el))
    {
      //определить операцию в очереди
      //определить операцию в стеке
      //выталкиваем или нет операции из стека
      //помещаем операцию в стек
      //выталкиваем операции из стека
    }
  }
  std::cout << pop();
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
