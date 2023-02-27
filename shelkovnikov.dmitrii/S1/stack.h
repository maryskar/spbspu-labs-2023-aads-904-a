#ifndef SPBSPU_LABS_2023_AADS_904_A_STACK_H
#define SPBSPU_LABS_2023_AADS_904_A_STACK_H
#include <cstddef>
#include <stdexcept>
#include "node.h"
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
      while (begin_)
      {
        drop();
      }
    }
    void push(T rhs)
    {
      Node< T > *node = new Node< T >(rhs);
      node->next_ = begin_;
      begin_ = node;
    }
    T drop()
    {
      if (empty())
      {
        throw std::logic_error("Check");
      }
      T data = begin_->data_;
      auto *node = begin_;
      begin_ = begin_->next_;
      delete node;
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
