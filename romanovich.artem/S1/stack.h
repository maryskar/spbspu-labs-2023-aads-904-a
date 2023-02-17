#ifndef STACK_H
#define STACK_H
#include <stdexcept>
template < typename T >
class Stack
{
public:
  Stack();
  ~Stack();
  T push(const T &value);
  T pop();
private:
  T *array_;
  size_t top_;
  size_t size_;
};
template < typename T >
Stack< T >::Stack():
  array_(new T)
{
}
template < typename T >
Stack< T >::~Stack()
{
  //delete ;
}
#endif
