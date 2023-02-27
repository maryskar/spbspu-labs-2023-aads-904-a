#ifndef SPBSPU_LABS_2023_AADS_904_A_QUEUE_H
#define SPBSPU_LABS_2023_AADS_904_A_QUEUE_H
#include <cstddef>
#include <stdexcept>
#include "node.h"
namespace dimkashelk
{
  template < typename T >
  class Queue
  {
  public:
    Queue():
      begin_(nullptr),
      end_(nullptr)
    {}
    Queue< T > (const Queue< T > &queue):
      begin_(nullptr),
      end_(nullptr)
    {
      Node< T > *start = queue.begin_;
      while (start)
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
      auto  *node = new Node< T >(rhs);
      if (empty())
      {
        begin_ = node;
      }
      else if (!end_)
      {
        end_ = node;
        begin_->next_ = end_;
      }
      else
      {
        end_->next_ = node;
        end_ = end_->next_;
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
    Node< T > *end_;
  };
}
#endif
