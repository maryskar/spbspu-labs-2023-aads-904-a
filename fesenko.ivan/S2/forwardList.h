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
    ForwardList();
    ForwardList(const ForwardList< T > &);
    ForwardList(ForwardList< T > &&);
    ForwardList< T > &operator=(const ForwardList< T > &);
    ForwardList< T > &operator=(ForwardList< T > &&);
    ~ForwardList();
  };
}
#endif
