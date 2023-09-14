#ifndef LIST_H
#define LIST_H
template< typename T >
struct List
{
  T data;
  List< T >* next;
};

template< typename T >
void clear(List< T >* first)
{
  while (first)
  {
    auto temp = first;
    first = first->next;
    delete temp;
  }
}
#endif
