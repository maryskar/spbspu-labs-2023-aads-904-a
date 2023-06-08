#ifndef S_Q_HELP_HPP
#define S_Q_HELP_HPP

#include "oneway-list.hpp"

namespace turkin
{
  template< typename T >
  void free(OneWayNode< T > * rhs)
  {
    while (rhs)
    {
      OneWayNode< T > * element = rhs;
      rhs = rhs->next;
      delete element;
    }
  }
};

#endif
