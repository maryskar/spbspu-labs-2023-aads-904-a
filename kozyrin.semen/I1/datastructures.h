#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

template< typename T>
struct box {
  box(T value, T* prev);
  T value_ = 0;
  T* prev_ = nullptr;
};

template< typename T >
class Queue {
public:
  Queue(box< T >* head, box< T >* tail);
  void push(T rhs);
  T drop();
private:
  box< T >* head_ = {0, 0};
  box< T >* tail_ = {0, 0};
};

template< typename T >
class Stack {
public:
  Stack(box< T >* top);
  void push(T rhs);
  T drop();
private:
  box< T >* top_ = {0, 0};
};

#endif
