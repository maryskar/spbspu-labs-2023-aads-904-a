#ifndef NODE_H
#define NODE_H
#include <tuple>
#include <stdexcept>
namespace details
{
  template < typename T >
  struct ListNode
  {
    T data_;
    ListNode< T > * next_;
  };

  template< typename T >
  void clear(ListNode< T > * node)
  {
    while (node)
    {
      ListNode< T > * newnode = node->next_;
      delete node;
      node = newnode;
    }
  }

  template< typename T >
  std::pair< ListNode< T > * , ListNode< T > * > copy(ListNode< T > * node)
  {
    ListNode< T > * newtop = new ListNode< T >{node->data_};
    ListNode< T > * newlast = newtop;
    node = node->next_;
    while (node != nullptr)
    {
      try
      {
        newlast->next_ = new ListNode< T >{node->data_};
      }
      catch (const std::exception & e)
      {
        clear(newtop);
        throw;
      }
      newlast = newlast->next_;
      node = node->next_;
    }
    return std::pair< ListNode< T > *, ListNode< T > * >{newtop, newlast};
  }
};

#endif
