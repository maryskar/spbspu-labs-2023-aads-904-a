#ifndef LIST_H
#define LIST_H

template< typename T >
class List
{
public:
  List(const T& data, List< T >* next);
  List(const List< T >& other);
  List< T >& operator=(const List< T >& other);
  T data;
  List< T >* next;
  ~List();
};

template< typename T >
List< T >::List(const T& data, List< T >* next) :
  data(data),
  next(next)
{}

template< typename T >
List< T >::~List()
{
  List< T >* current = this;
  while (current != nullptr)
  {
    List< T >* temp = current;
    current = current->next;
    delete temp;
  }
}

template< typename T >
List< T >::List(const List< T >& other):
  data(other.data),
  next(nullptr)
{
  if (other.next != nullptr)
  {
    next = new List< T >(*other.next);
  }
}

template< typename T >
List< T >& List< T >::operator=(const List< T >& other)
{
  if (this != &other)
  {
    data = other.data;
    if (next != nullptr)
    {
      delete next;
    }
    next = nullptr;
    if (other.next != nullptr)
    {
      next = new List< T >(*other.next);
    }
  }
  return *this;
}
#endif
