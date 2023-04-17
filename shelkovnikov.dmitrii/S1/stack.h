#ifndef SPBSPU_LABS_2023_AADS_904_A_STACK_H
#define SPBSPU_LABS_2023_AADS_904_A_STACK_H
#include <cstddef>
#include <stdexcept>
#include "nodeOneWayList.h"
namespace dimkashelk
{
  template < typename T >
  class Stack
  {
  public:
    Stack():
      begin_(nullptr)
    {}
    Stack(const Stack< T > &stack):
      begin_(details::copy(stack.begin_).first)
    {}
    Stack(Stack< T > &&stack):
      begin_(stack.begin_)
    {
      stack.begin_ = nullptr;
    }
    ~Stack()
    {
      details::freeList< T >(begin_);
      begin_ = nullptr;
    }
    Stack< T > &operator=(const Stack< T > &stack)
    {
      if (std::addressof(stack) == this)
      {
        return *this;
      }
      details::freeList< T >(begin_);
      begin_ = details::copy(stack).first;
      return *this;
    }
    Stack< T > &operator=(Stack< T > &&stack)
    {
      if (std::addressof(stack) == this)
      {
        return *this;
      }
      details::freeList< T >(begin_);
      begin_ = stack.begin_;
      stack.begin_ = nullptr;
      return *this;
    }
    void pushFront(const T &rhs)
    {
      begin_ = new details::NodeOneWayList< T >(rhs, begin_);
    }
    T &last()
    {
      if (empty())
      {
        throw std::logic_error("Check");
      }
      return begin_->data;
    }
    const T &last() const
    {
      if (empty())
      {
        throw std::logic_error("Check");
      }
      return begin_->data;
    }
    void popBack()
    {
      if (empty())
      {
        throw std::logic_error("Check");
      }
      details::NodeOneWayList< T > *node = begin_;
      begin_ = begin_->next;
      delete node;
    }
    bool empty() const
    {
      return begin_ == nullptr;
    }
  private:
    details::NodeOneWayList< T > *begin_;
  };
}
#endif
