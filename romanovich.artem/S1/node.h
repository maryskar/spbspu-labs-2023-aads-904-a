#ifndef NODE_H
#define NODE_H
#include <stdexcept>
template < typename T >
class Node
{
public:
  Node();
  ~Node();
private:
  T *top_;
  size_t size_;
};
#endif