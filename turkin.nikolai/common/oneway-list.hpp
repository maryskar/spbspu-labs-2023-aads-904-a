#ifndef ONEWAY_LIST_HPP
#define ONEWAY_LIST_HPP

#include <utility>

namespace turkin
{
  namespace pattern
  {
    template< typename T >
    struct OneWayNode
    {
      T data;
      OneWayNode< T > * next;
    };

    template< typename T >
    std::pair< OneWayNode< T > *, OneWayNode< T > * > copyList(OneWayNode< T > * rhs)
    {
      if (!rhs)
      {
        return std::make_pair(nullptr, nullptr);
      }
      OneWayNode< T > * source = rhs;
      OneWayNode< T > * clone = new OneWayNode< T > {source->data, nullptr};
      OneWayNode< T > * start = clone;
      //OneWayNode< T > * end = nullptr;
      while (source->next)
      {
        clone->next = new OneWayNode< T > {source->next->data, nullptr};
        //end = clone;
        clone = clone->next;
        source = source->next;
      }
      return std::make_pair(start, clone);
    }
  };
};

#endif
