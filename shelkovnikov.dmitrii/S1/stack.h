#ifndef SPBSPU_LABS_2023_AADS_904_A_STACK_H
#define SPBSPU_LABS_2023_AADS_904_A_STACK_H
#include <cstddef>
#include <stdexcept>
#include "nodeOfDataClass.h"
#include "freeList.h"
namespace dimkashelk
{
  template < typename T >
  class Stack
  {
  public:
    Stack():
      begin_(nullptr)
    {}
    ~Stack()
    {
      details::freeList< T >(begin_);
      begin_ = nullptr;
    }
    void push(const T &rhs)
    {
      auto *node = new details::NodeOfDataClass< T >(rhs);
      node->next = begin_;
      begin_ = node;
    }
    T &last()
    {
      if (empty())
      {
        throw std::logic_error("Check");
      }
      return begin_->data;
    }
    void pop_back()
    {
      if (empty())
      {
        throw std::logic_error("Check");
      }
      details::NodeOfDataClass< T > *node = begin_;
      begin_ = begin_->next;
      delete node;
    }
    bool empty() const
    {
      return begin_ == nullptr;
    }
  private:
    details::NodeOfDataClass< T > *begin_;
  };
}
#endif
