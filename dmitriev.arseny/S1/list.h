#ifndef LIST_H
#define LIST_H

template< typename T >
struct List
{
  T data;
  T* next;

  List(T data = T(), T* next = nullptr);
};

template<typename T>
inline List<T>::List(T data, T* next):
  data(data),
  next(next)
{

}

#endif
