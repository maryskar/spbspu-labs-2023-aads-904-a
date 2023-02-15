#ifndef SPBSPU_LABS_2023_AADS_904_A_QUEUE_H
#define SPBSPU_LABS_2023_AADS_904_A_QUEUE_H
#include <cstddef>
#include <stdexcept>
#include <list>
#include "expand.h"
#include "node.h"
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
      Node< T > *start = queue.begin_;
      while (start != nullptr)
      {
        push(start->data_);
        start = start->next_;
      }
    }
    ~Queue()
    {
      while (begin_)
      {
        drop();
      }
    }
    void push(T rhs)
    {
      Node< T >  *node = new Node< T >(rhs);
      Node< T > *first = begin_;
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
      Node< T > *obj = begin_;
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
    Node< T > *begin_;
  };
}
#endif
