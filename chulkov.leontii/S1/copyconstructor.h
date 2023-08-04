#ifndef COPYCONSTRUCTOR_H
#define COPYCONSTRUCTOR_H
#include "list.h"

namespace chulkov {
  template < typename T >
  void copyList(List< T >*& dest, const List< T >* src);
}

#endif
