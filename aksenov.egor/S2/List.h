#ifndef LIST_H
#define LIST_H
namespace aksenov
{
  template< typename T >
  struct listT
  {
    T data;
    listT< T > *next;
  };
}
#endif
