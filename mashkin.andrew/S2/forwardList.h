#ifndef FORWARDLIST_H
#define FORWARDLIST_H

template< class T >
class ForwardList
{
public:
  T push();
  T pop();
private:
  T data;
  ForwardList< T >* next;
};
#endif
