#ifndef LIST_H
#define LIST_H
#include <utility>
namespace timofeev
{
  template< typename T >
  struct List
  {
    T data;
    List< T >* next;

    List():
      data(),
      next(nullptr)
    {}
    List(const T &other):
      data(other),
      next(nullptr)
    {}
    List(const T &rhs, List< T > *val):
      data(rhs),
      next(val)
    {}
  };
  template< typename T >
  void clearlist(List< T >* top)
  {
    while (top)
    {
      auto tmp = top;
      top = top->next;
      delete tmp;
    }
  }

  template< typename T >
  std::pair< List< T > *, List< T > * > copy(List< T > *top)
  {
    if (!top)
    {
      return {nullptr, nullptr};
    }
    auto* new_top = new List< T >(top->data);
    List< T >* prev = new_top;
    for (List< T >* current = top->next; current; current = current->next)
    {
      auto* node = new List< T >(current->data);
      prev->next = node;
      prev = node;
    }
    prev->next = nullptr;
    return {new_top, prev};
  }
}
#endif
