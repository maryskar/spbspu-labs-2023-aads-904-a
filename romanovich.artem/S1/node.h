#ifndef NODE_H
#define NODE_H
#include <stdexcept>
#include "operations.h"
#include "parenthesis.h"
namespace details
{
  template< typename T >
  struct ListNode
  {
    T data_;
    ListNode< T > *next_;
  };
  template< typename T >
  void clear(ListNode< T > *node)
  {
    while (node)
    {
      ListNode< T > *nextNode = node->next_;
      delete node;
      node = nextNode;
    }
  }
  template< typename T >
  std::tuple< ListNode< T > *, ListNode< T > * > copy(const ListNode< T > *listNode)
  {
    if (listNode == nullptr)
    {
      return {nullptr, nullptr};
    }
    ListNode< T > *node = listNode;
    ListNode< T > *begin = new ListNode< T >{node->data, nullptr};
    ListNode< T > *end = nullptr;
    try
    {
      while (node != nullptr)
      {
        node = node->data;
        begin->next_ = new details::ListNode< T >{node->data, nullptr};
        end = begin;
        begin = begin->next_;
      }
    }
    catch (...)
    {
      clear(begin);
      throw;
    }
    return {begin, end};
  }
}
#endif
