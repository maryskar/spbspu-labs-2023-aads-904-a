#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

namespace potapova
{
  template< typename T >
  struct List
  {
    T data;
    List< T >* next;
  };
}

#endif
