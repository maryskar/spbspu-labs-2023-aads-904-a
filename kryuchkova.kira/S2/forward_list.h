#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H
#include <iterator>
#include <initializer_list>
#include "forward_list_const_iterator.h"
#include "forward_list_iterator.h"

namespace kryuchkova
{
  template< typename T >
  class ForwardList
  {
  public:
    using iterator = ForwardIterator< T >;
    using const_iterator = ConstForwardIterator< T >;
    using this_t = ForwardList< T >;
    ForwardList();
    ForwardList(const this_t & rhs);
    ForwardList(this_t && rhs);
    ForwardList(std::initializer_list< T > init);
    ~ForwardList();

    this_t & operator=(const this_t & fwdlst);
    this_t & operator=(this_t && fwdlst);
    this_t & operator=(std::initializer_list< T > init);

    iterator insert_after(const_iterator pos, const T & val);
    iterator insert_after(const_iterator pos, T && val);
    iterator insert_after(const_iterator pos, std::size_t n, const T & val);

    iterator before_begin() noexcept;
    const_iterator before_begin() const noexcept;
    const_iterator cbefore_begin() const noexcept;
    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noecept;
    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;
    iterator last() noexcept;
    const_iterator last() const noexcept;
    const_iterator clast() const noexcept;

    bool IsEmpty() const noexcept;
    void clear() noexcept;

  };
}

#endif
