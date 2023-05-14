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

    template< typename T >
    T remove(pattern::OneWayNode< T > * rhs)
    {
      pattern::OneWayNode< T > * element = rhs;
      rhs = element->next;
      T ret = element->data;
      delete element;
      return ret;
    }
  }
};

#endif
