#ifndef SPBSPU_LABS_2023_AADS_904_A_QUEUE_H
#define SPBSPU_LABS_2023_AADS_904_A_QUEUE_H
#include <cstddef>
#include <stdexcept>
#include <list>
#include "expand.h"
namespace dimkashelk
{
  template < typename T >
  class Queue
  {
  public:
    Queue():
      begin_(nullptr)
    {}
    Queue< T > (const Queue< T > &queue):
      begin_(nullptr)
    {
      Node *start = queue.begin_;
      while (start != nullptr)
      {
        push(start->data_);
        start = start->next_;
      }
    }
    void push(T rhs)
    {
      Node *node = new Node(rhs);
      Node *first = begin_;
      if (empty())
      {
        begin_ = node;
      }
      else
      {
        while (first->next_)
        {
          first = first->next_;
        }
        first->next_ = node;
      }
    }
    T drop()
    {
      if (begin_ == nullptr)
      {
        throw std::logic_error("Check");
      }
      Node *obj = begin_;
      T data = obj->data_;
      begin_ = begin_->next_;
      delete obj;
      return data;
    }
    bool empty() const
    {
      return begin_ == nullptr;
    }
  private:
    struct Node
    {
      T data_;
      Node *next_;
      explicit Node(T rhs):
        data_(rhs),
        next_(nullptr)
      {}
    };
    Node *begin_;
  };
}
#endif
