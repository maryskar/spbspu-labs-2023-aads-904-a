#ifndef S2_FORWARD_LIST_HPP
#define S2_FORWARD_LIST_HPP
#include <initializer_list>
#include "forward-iterator.hpp"
#include "const-forward-iterator.hpp"

namespace chemodurov
{
  template< typename T >
  class ForwardList
  {
   public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type &;
    using const_reference = const value_type &;
    using iterator = ForwardIterator< T >;
    using const_iterator = ConstForwardIterator< T >;
    ForwardList();
    ForwardList(const ForwardList< T > & list);
    ForwardList(ForwardList< T > && list);
    ForwardList(std::initializer_list< T > init);
    ~ForwardList();
    ForwardList< T > & operator=(const ForwardList< T > & list);
    ForwardList< T > & operator=(ForwardList< T > && list);
  };
}

#endif
