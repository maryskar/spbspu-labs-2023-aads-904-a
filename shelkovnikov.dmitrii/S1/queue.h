#ifndef SPBSPU_LABS_2023_AADS_904_A_QUEUE_H
#define SPBSPU_LABS_2023_AADS_904_A_QUEUE_H
#include <cstddef>
#include <stdexcept>
#include "nodeOfDataClass.h"
#include "freeList.h"
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
    Queue< T >(const Queue< T > &queue):
      begin_(nullptr),
      end_(nullptr)
    {
      details::NodeOfDataClass< T > *start = queue.begin_;
      while (start)
      {
        push(start->data);
        start = start->next;
      }
    }
    Queue< T >(Queue< T > &&queue):
      begin_(queue.begin_),
      end_(queue.end_)
    {
      queue.begin_ = nullptr;
      queue.end_ = nullptr;
    }
    ~Queue()
    {
      free();
    }
    Queue< T > &operator=(const Queue< T > &queue)
    {
      free();
      details::NodeOfDataClass< T > *start = queue.begin_;
      while (start)
      {
        push(start->data);
        start = start->next;
      }
      return *this;
    }
    Queue< T > &operator=(Queue< T > &&queue)
    {
      if (this == std::addressof(queue))
      {
        return *this;
      }
      free();
      begin_ = queue.begin_;
      end_ = queue.end_;
      queue.begin_ = nullptr;
      queue.end_ = nullptr;
    }
    void push(const T &rhs)
    {
      auto *node = new details::NodeOfDataClass< T >(rhs);
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
    T &drop()
    {
      if (begin_ == nullptr)
      {
        throw std::logic_error("Check");
      }
      details::NodeOfDataClass< T > *obj = begin_;
      T &data = obj->data;
      begin_ = begin_->next;
      delete obj;
      return data;
    }
    bool empty() const
    {
      return begin_ == nullptr;
    }
  private:
    details::NodeOfDataClass< T > *begin_;
    details::NodeOfDataClass< T > *end_;
    void free()
    {
      details::freeList< T >(begin_);
      begin_ = nullptr;
      end_ = nullptr;
    }
  };
}
#endif
