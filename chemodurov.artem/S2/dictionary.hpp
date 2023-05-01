#ifndef S2_DICTIONARY_HPP
#define S2_DICTIONARY_HPP
#include <cmath>
#include "forward-list.hpp"

namespace chemodurov
{
  template< typename Key, typename Value, typename Compare >
  class Dictionary
  {
   public:
    using key_type = Key;
    using mapped_type = Value;
    using value_type = std::pair< const Key, Value >;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using key_compare = Compare;
    using reference = value_type &;
    using const_reference = const value_type &;
    using iterator = ForwardIterator< value_type >;
    using const_iterator = ConstForwardIterator< value_type >;
    using this_t = Dictionary< Key, Value, Compare >;
    class value_compare;
    Dictionary();
    Dictionary(const this_t & other);
    Dictionary(this_t && other);
    explicit Dictionary(const Compare & comp);
    template< typename InputIt >
    Dictionary(InputIt first, InputIt last, const Compare & comp = Compare());
    template< typename InputIt >
    Dictionary(InputIt first, InputIt last);
    Dictionary(std::initializer_list< value_type > init, const Compare & comp = Compare());
    Dictionary(std::initializer_list< value_type > init);
    ~Dictionary();
    this_t & operator=(const this_t & other);
    this_t & operator=(this_t && other);
    this_t & operator=(std::initializer_list< value_type > init);
    Value & operator[](const key_type & key);
    Value & operator[](key_type && key);
    Value & at(const key_type & key);
    const Value & at(const key_type & key) const;
    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;
    bool empty() const noexcept;
    size_type size() const noexcept;
    void clear() noexcept;
    std::pair< iterator, bool > insert(const_reference value);
    template< typename P >
    std::pair< iterator, bool > insert(P && value);
    iterator insert_after(const_iterator pos, const_reference value);
    template< typename P >
    iterator insert_after(const_iterator pos, P && value);
    template< typename InputIt >
    void insert(InputIt first, InputIt last);
    void insert(std::initializer_list< value_type > init);
    template< typename... Args >
    std::pair< iterator, bool > emplace(Args && ... args);
    template< typename... Args >
    iterator emplace_after(const_iterator pos, Args && ... args);
    iterator erase_after(const_iterator pos);
    iterator erase_after(const_iterator first, const_iterator last);
    size_type erase(const key_type & key);
    void swap(this_t & other);
    size_type count(const key_type & key);
    template< typename K >
    size_type count(const K & k);
    iterator find(const key_type & key);
    const_iterator find(const key_type & key) const;
    template< typename K >
    iterator find(const K & x);
    template< typename K >
    const_iterator find(const K & x) const;
    std::pair< iterator, iterator > equal_range(const key_type & key);
    std::pair< const_iterator, const_iterator > equal_range(const key_type & key) const;
    template< typename K >
    std::pair< iterator, iterator > equal_range(const K & x);
    template< typename K >
    std::pair< const_iterator, const_iterator > equal_range(const K & x) const;
    iterator lower_bound(const key_type & key);
    const_iterator lower_bound(const key_type & key) const;
    template< typename K >
    iterator lower_bound(const K & x);
    template< typename K >
    const_iterator lower_bound(const K & x) const;
    iterator upper_bound(const key_type & key);
    const_iterator upper_bound(const key_type & key) const;
    template< typename K >
    iterator upper_bound(const K & x);
    template< typename K >
    const_iterator upper_bound(const K & x) const;
    key_compare key_comp() const;
    value_compare value_comp() const;
   private:
    ForwardList< value_type > data_;
    Compare comp_;
    size_type size_;
  };

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::key_compare Dictionary< Key, Value, Compare >::key_comp() const
  {
    return comp_;
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::value_compare Dictionary< Key, Value, Compare >::value_comp() const
  {
    return value_compare(comp_);
  }

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare >::Dictionary():
   data_(),
   comp_(),
   size_(0)
  {}

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare >::Dictionary(const this_t & other):
   data_(other.data_),
   comp_(other.comp_),
   size_(other.size_)
  {}

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare >::Dictionary(this_t && other):
   data_(std::move(other.data_)),
   comp_(std::move(other.comp_)),
   size_(other.size_)
  {}

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare >::Dictionary(const Compare & comp):
   data_(),
   comp_(comp),
   size_(0)
  {}

  template< typename Key, typename Value, typename Compare >
  template< typename InputIt >
  Dictionary< Key, Value, Compare >::Dictionary(InputIt first, InputIt last, const Compare & comp):
   data_(first, last),
   comp_(comp),
   size_(std::abs(std::distance(first, last)))
  {}

  template< typename Key, typename Value, typename Compare >
  template< typename InputIt >
  Dictionary< Key, Value, Compare >::Dictionary(InputIt first, InputIt last):
   Dictionary(first, last, Compare())
  {}

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare >::Dictionary(std::initializer_list< value_type > init, const Compare & comp):
   data_(init),
   comp_(comp),
   size_(init.size())
  {}

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare >::Dictionary(std::initializer_list< value_type > init):
    Dictionary(init, Compare())
  {}

  template< typename Key, typename Value, typename Compare >
  class Dictionary< Key, Value, Compare >::value_compare
  {
   public:
    using result_type = bool;
    using first_argument_type = value_type;
    using second_argument_type = value_type;
    bool operator()( const value_type& lhs, const value_type& rhs ) const
    {
      return comp(lhs.first, rhs.first);
    };
   protected:
    Compare comp;
    value_compare(Compare c): comp(c) {};
  };
}
#endif
