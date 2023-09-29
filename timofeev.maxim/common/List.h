#ifndef LIST_H
#define LIST_H
namespace timofeev
{
  template< typename T >
  struct List
  {
    List():
      data(),
      next(nullptr)
    {}
    List(const T &other):
      data(other),
      next(nullptr)
    {}

    T data;
    List< T >* next;
  };
  template< typename T >
  void clear(List< T >* top)
  {
    while (top)
    {
      auto tmp = top;
      top = top->next;
      delete tmp;
    }
  }
}
#endif
