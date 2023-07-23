#ifndef FORWARDLIST_H
#define FORWARDLIST_H
#include "forwardIterator.h"
#include "constForwardIterator.h"
namespace fesenko
{
  template< typename T >
  class ForwardList
  {
   public:
    using value_type = T;
    using reference = value_type &;
    using const_reference = const value_type &;
    using iterator = ForwardIterator< T >;
    using const_iterator = ConstForwardIterator< T >;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using this_t = ForwardList< T >;
    ForwardList();
    ForwardList(const this_t &);
    ForwardList(this_t &&);
    ForwardList< T > &operator=(const this_t &);
    ForwardList< T > &operator=(this_t &&);
    ~ForwardList();
  };
}
#endif
