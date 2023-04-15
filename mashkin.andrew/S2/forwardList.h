#ifndef FORWARDLIST_H
#define FORWARDLIST_H
#include "iterator.h"
#include "nodeList.h"

namespace mashkin
{
  template< class T >
  class ForwardList
  {
  public:
    ForwardList();
    Iterator< T > begin() noexcept;
    Iterator< T > end() noexcept;
    void push();
    T pop();

    bool isEmpty() const;

  private:
    nodeList< T >* head;
    nodeList< T >* tail;
  };
}

template< class T >
mashkin::ForwardList< T >::ForwardList()
{
}

template< class T >
void mashkin::ForwardList< T >::push()
{

}

template< class T >
bool mashkin::ForwardList< T >::isEmpty() const
{
}
#endif
