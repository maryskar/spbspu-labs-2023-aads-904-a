#ifndef NODE_H
#define NODE_H
#include <tuple>
namespace romanovich
{
  namespace details
  {
    template< typename T >
    struct ListNode
    {
      T data_;
      ListNode< T > *next_;
      explicit ListNode(const T &value);
      ListNode(const T &value, ListNode *next);
      explicit ListNode(const T &&value);
      ListNode(T &&value, ListNode *next);
    };
    template< typename T >
    ListNode< T >::ListNode(const T &value):
      data_(value),
      next_(nullptr)
    {
    }
    template< typename T >
    ListNode< T >::ListNode(const T &value, ListNode *next):
      data_(value),
      next_(next)
    {
    }
    template< typename T >
    ListNode< T >::ListNode(const T &&value):
      data_(std::move(value)),
      next_(nullptr)
    {
    }
    template< typename T >
    ListNode< T >::ListNode(T &&value, ListNode *next):
      data_(std::move(value)),
      next_(next)
    {
    }
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
      if (!listNode)
      {
        return {nullptr, nullptr};
      }
      const ListNode< T > *node = listNode;
      ListNode< T > *begin = new ListNode< T >{node->data_, nullptr};
      ListNode< T > *end = begin;
      try
      {
        while (node->next_)
        {
          node = node->next_;
          end->next_ = new details::ListNode< T >{node->data_, nullptr};
          end = end->next_;
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
}
#endif
