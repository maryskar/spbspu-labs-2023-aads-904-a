#ifndef S_Q_HELP_HPP
#define S_Q_HELP_HPP

#include "oneway-list.hpp"

namespace turkin
{
  namespace sqhelp
  {
    template< typename T >
    void free(pattern::OneWayNode< T > * rhs)
    {
      while (rhs)
      {
        pattern::OneWayNode< T > * element = rhs;
        rhs = rhs->next;
        delete element;
      }
    }
  }
};

#endif
