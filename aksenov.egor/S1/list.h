#ifndef LIST_H
#define LIST_H
namespace aksenov {
  template< typename T >
  struct List
  {
    T data;
    List< T > *next;
  };
}
#endif
