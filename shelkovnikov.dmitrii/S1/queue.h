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
      details::NodeOfDataStruct< T > *start = queue.begin_;
      while (start)
      {
        push(start->data);
        start = start->next;
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
      auto  *node = new details::NodeOfDataStruct< T >(rhs);
      if (empty())
      {
        begin_ = node;
      }
      else if (!end_)
      {
        end_ = node;
        begin_->next = end_;
      }
      else
      {
        end_->next = node;
        end_ = end_->next;
      }
    }
    T drop()
    {
      if (begin_ == nullptr)
      {
        throw std::logic_error("Check");
      }
      details::NodeOfDataStruct< T > *obj = begin_;
      T data = obj->data;
      begin_ = begin_->next;
      delete obj;
      return data;
    }
    bool empty() const
    {
      return begin_ == nullptr;
    }
  private:
    details::NodeOfDataStruct< T > *begin_;
    details::NodeOfDataStruct< T > *end_;
  };
}
#endif
