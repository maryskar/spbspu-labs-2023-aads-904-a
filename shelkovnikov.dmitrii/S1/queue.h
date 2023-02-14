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
      begin(nullptr)
    {}
    Queue< T > (const Queue< T > &queue):
      begin(nullptr)
    {
      Node *start = queue.begin;
      while (start != nullptr)
      {
        push(start->data);
        start = start->next;
      }
    }
    void push(T rhs)
    {
      Node *node = new Node(rhs);
      Node *first = begin;
      if (empty())
      {
        begin = node;
      }
      else
      {
        while (first->next)
        {
          first = first->next;
        }
        first->next = node;
      }
    }
    T drop()
    {
      if (begin == nullptr)
      {
        throw std::logic_error("Check");
      }
      Node obj = *begin;
      begin = begin->next;
      return obj.data;
    }
    bool empty() const
    {
      return begin == nullptr;
    }
  private:
    struct Node
    {
      T data;
      Node *next;
      explicit Node(T rhs):
        data(rhs),
        next(nullptr)
      {}
    };
    Node *begin;
  };
}
#endif
