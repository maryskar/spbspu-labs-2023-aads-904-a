#ifndef LIST_H
#define LIST_H
namespace skarlygina
{
  template < typename T >
  struct List
  {
    T data;
    List< T >* next;
  };
}
#endif