#ifndef ONEWAY_LIST_HPP
#define ONEWAY_LIST_HPP

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
    OneWayNode< T > * copyList(OneWayNode< T > * rhs)
    {
      if (!rhs)
      {
        return nullptr;
      }
      OneWayNode< T > * source = rhs;
      OneWayNode< T > * clone = new OneWayNode< T > {source->data, nullptr};
      OneWayNode< T > * start = clone;
      while (source->next)
      {
        clone->next = new OneWayNode< T > {source->next->data, nullptr};
        clone = clone->next;
        source = source->next;
      }
      return start;
    }
  };
};

#endif
