#ifndef DICTIONARY_H
#define DICTIONARY_H
#include "forward_list.h"
#include "forward_list_const_iterator.h"
#include "forward_list_iterator.h"

namespace kryuchkova
{
  template< typename T >
  class ForwardList;
  template< typename T >
  class ConstForwardIterator;
  template< typename T >
  class ForwardList;

  template< typename Key, typename Value, typename Compare = std::less< > >
  class Dictionary 
  {
  public:
    using key_type = Key;
    using val = value;
    using this_t = Dictionary< Key, Value, Compare >;
    using val_type = std::pair< const Key, Value >;
    using iterator = ForwardIterator< T >;
    using const_iterator = ConstForwardIterator< T >;

    Dictionary();
    Dictionary(const this_t & other);
    Dictionary(this_t && other);
    explicit Dictionary(const Compare & comp);
    Dictionary(std::initializer_list< val_type > init, const Compare & comp = Compare());
    ~Dictionary() = default;

    this_t & operator=(const this_t & other);
    this_t & operator=(this_t && other);
    this_t & operator=(std::initializer_list< val_type > init);
    val & operator[](const key_type & key);
    val & operator[](key_type && key);
    const val & at(const key_type & key) const;

    iterator before_begin() noexcept;
    const_iterator before_begin() const noexcept;
    const_iterator cbefore_begin() const noexcept;
    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;
    iterator last() noexcept;
    const_iterator last() const noexcept;
    const_iterator clast() const noexcept;

    iterator insert(const_iterator pos, const val_type & val);
    iterator erase_after(const_iterator pos);
    iterator erase_after(const_iterator first, const_iterator last);
    iterator find(const key_type & key);
    const_iterator find(const key_type & key) const;

    std::pair< iterator, bool > insert(const val_type & val);
    std::pair< iterator, iterator > equal_range(const key_type & key);
    std::pair< const_iterator, const_iterator > equal_range(const key_type & key) const;

    bool IsEmpty() const noexcept;
    bool isEqualTo(const this_t & other) const noexcept;
    void clear() noexcept;
    void insert(std::initializer_list< value_type > init);
    void swap(this_t & other);
    std::size_t size() const noexcept;
    std::size_t erase(const key_type & key);
    std::size_t count(const key_type & key) const;
    Compare key_comp() const;
  
  private:
    ForwardList< val_type > data_;
    std::size_t size_;
    Compare comp_;
  };
}

#endif
