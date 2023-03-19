#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

template< typename T >
struct qBox {
  T value_ = 0;
  qBox< T >* prev_ = nullptr;
  qBox< T >* next_ = nullptr;
};

template< typename T >
class Queue {
public:
  Queue();
  ~Queue();
  void push(T rhs);
  T drop();
private:
  qBox< T >* head_ = nullptr;
  qBox< T >* tail_ = nullptr;
};


#endif
