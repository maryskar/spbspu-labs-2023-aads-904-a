#ifndef NODE_H
#define NODE_H

namespace details
{
  template < typename T >
  struct ListNode
  {
    T data_;
    ListNode< T > * next_;
  };
}

#endif
