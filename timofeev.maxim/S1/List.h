#ifndef LIST_H
#define LIST_H
namespace timofeev
{
  template< typename T >
  struct List
  {
    T data;
    List< T >* next;
  };
  template< typename T >
  void clear(List< T >* top)
  {
    while(top)
    {
      auto tmp = top;
      top = top->next;
      delete tmp;
    }
  }
}
#endif
