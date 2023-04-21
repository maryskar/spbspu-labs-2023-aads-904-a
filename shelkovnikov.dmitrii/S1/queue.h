#ifndef SPBSPU_LABS_2023_AADS_904_A_QUEUE_H
#define SPBSPU_LABS_2023_AADS_904_A_QUEUE_H
#include <cstddef>
#include <stdexcept>
#include "nodeOneWayList.h"
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
      auto copy_res = details::copy(queue.begin_);
      begin_ = copy_res.first;
      end_ = copy_res.second;
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
      if (std::addressof(queue) == this)
      {
        return *this;
      }
      auto res_copy = details::copy(queue.begin_);
      free();
      begin_ = res_copy.first;
      end_ = res_copy.second;
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
      auto *node = new details::NodeOneWayList< T >(rhs);
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
    T &front()
    {
      if (begin_ == nullptr)
      {
        throw std::logic_error("Check");
      }
      return begin_->data;
    }
    const T &front() const
    {
      if (empty())
      {
        throw std::logic_error("Check");
      }
      return begin_->data;
    }
    void popFront()
    {
      if (begin_ == nullptr)
      {
        throw std::logic_error("Check");
      }
      details::NodeOneWayList< T > *node = begin_;
      begin_ = begin_->next;
      if (begin_ == end_)
      {
        end_ = nullptr;
      }
      delete node;
    }
    bool empty() const
    {
      return begin_ == nullptr;
    }
  private:
    details::NodeOneWayList< T > *begin_;
    details::NodeOneWayList< T > *end_;
    void free()
    {
      details::freeList< T >(begin_);
      begin_ = nullptr;
      end_ = nullptr;
    }
  };
}
#endif
