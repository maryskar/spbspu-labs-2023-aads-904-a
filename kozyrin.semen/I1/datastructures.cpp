#include "datastructures.h"

template< typename T >
box< T >::box(T value, T* prev):
  value_(value),
  prev_(prev)
{}

template< typename T >
Queue< T >::Queue(box< T >* head, box< T >* tail):
  head_(head),
  tail_(tail)
{}

template< typename T >
Stack< T >::Stack(box< T >* top):
  top_(top)
{}
