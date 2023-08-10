#ifndef FORWARDLIST_H
#define FORWARDLIST_H

#include "singlyLinkedList.h"

namespace potapova
{
  template< typename T >
  class ForwardList
  {
    private:
      List< T >* node;
  };
}

#endif
