#ifndef S2_FORWARD_LIST_HPP
#define S2_FORWARD_LIST_HPP
#include <initializer_list>
#include <iterator>
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
    using this_t = ForwardList< T >;
    ForwardList();
    ForwardList(const this_t & rhs);
    ForwardList(this_t && rhs);
    ForwardList(std::initializer_list< T > init);
    ~ForwardList();
    this_t & operator=(const this_t & rhs);
    this_t & operator=(this_t && rhs);
    bool operator==(const this_t & rhs);
    bool operator!=(const this_t & rhs);
    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;
    bool empty() const noexcept;
    size_type max_size() const noexcept;
   private:
    iterator begin_;
    iterator end_;
  };
}

#endif
