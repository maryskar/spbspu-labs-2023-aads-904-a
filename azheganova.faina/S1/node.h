#ifndef NODE_H
#define NODE_H

template < typename T >
struct ListNode
{
  T data_;
  ListNode< T > *next_;
};

#endif
