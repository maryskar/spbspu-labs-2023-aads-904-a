#include "node.h"

template< typename T >
Node< T >::Node(T value, Node* p_next):
  value(value),
  p_next(p_next)
{}
