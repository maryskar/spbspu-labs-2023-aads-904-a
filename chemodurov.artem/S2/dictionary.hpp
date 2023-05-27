#ifndef S2_DICTIONARY_HPP
#define S2_DICTIONARY_HPP
#include <type_traits>
#include "forward-list.hpp"

namespace chemodurov
{
  template< typename Key, typename Value, typename Compare = std::less< > >
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
    using iterator = typename ForwardList< value_type >::iterator;
    using const_iterator = typename ForwardList< value_type >::const_iterator;
    using this_t = Dictionary< Key, Value, Compare >;
    class value_compare;
    Dictionary();
    Dictionary(const this_t & other);
    Dictionary(this_t && other);
    explicit Dictionary(const Compare & comp);
    template< typename InputIt >
    Dictionary(InputIt first, InputIt last, const Compare & comp = Compare());
    Dictionary(std::initializer_list< value_type > init, const Compare & comp = Compare());
    ~Dictionary() = default;
    this_t & operator=(const this_t & other);
    this_t & operator=(this_t && other);
    this_t & operator=(std::initializer_list< value_type > init);
    mapped_type & operator[](const key_type & key);
    mapped_type & operator[](key_type && key);
    mapped_type & at(const key_type & key);
    const mapped_type & at(const key_type & key) const;
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
    bool empty() const noexcept;
    size_type size() const noexcept;
    void clear() noexcept;
    std::pair< iterator, bool > insert(const_reference value);
    template< typename P >
    std::pair< iterator, bool > insert(P && value);
    iterator insert(const_iterator pos, const_reference value);
    template< typename P >
    iterator insert(const_iterator pos, P && value);
    template< typename InputIt >
    void insert(InputIt first, InputIt last);
    void insert(std::initializer_list< value_type > init);
    template< typename... Args >
    std::pair< iterator, bool > emplace(Args && ... args);
    template< typename... Args >
    iterator emplace(const_iterator pos, Args && ... args);
    iterator erase_after(const_iterator pos);
    iterator erase_after(const_iterator first, const_iterator last);
    size_type erase(const key_type & key);
    void swap(this_t & other);
    size_type count(const key_type & key) const;
    iterator find(const key_type & key);
    const_iterator find(const key_type & key) const;
    std::pair< iterator, iterator > equal_range(const key_type & key);
    std::pair< const_iterator, const_iterator > equal_range(const key_type & key) const;
    iterator lower_bound(const key_type & key);
    const_iterator lower_bound(const key_type & key) const;
    iterator upper_bound(const key_type & key);
    const_iterator upper_bound(const key_type & key) const;
    key_compare key_comp() const;
    value_compare value_comp() const;
    bool isEqualTo(const this_t & other) const noexcept;
   private:
    ForwardList< value_type > data_;
    Compare comp_;
    size_type size_;
  };

  void print(std::ostream & out, const std::pair< int, std::string > & pair);
  void print(std::ostream & out, const Dictionary< int, std::string > & dict);
  void print(std::ostream & out, const std::pair< std::string, Dictionary< int, std::string > > & pair);

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
  {
    other.size_ = 0;
  }

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
  Dictionary< Key, Value, Compare >::Dictionary(std::initializer_list< value_type > init, const Compare & comp):
   data_(init),
   comp_(comp),
   size_(init.size())
  {}

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare > & Dictionary< Key, Value, Compare >::operator=(const this_t & other)
  {
    if (this == std::addressof(other))
    {
      return *this;
    }
    Compare temp = other.comp_;
    data_ = other.data_;
    comp_ = std::move(temp);
    size_ = other.size_;
    return *this;
  }

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare > & Dictionary< Key, Value, Compare >::operator=(this_t && other)
  {
    if (this == std::addressof(other))
    {
      return *this;
    }
    data_ = std::move(other.data_);
    comp_ = std::move(other.comp_);
    size_ = other.size_;
    other.size_ = 0;
    return *this;
  }

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare > & Dictionary< Key, Value, Compare >::operator=(std::initializer_list< value_type > init)
  {
    clear();
    data_ = init;
    comp_ = Compare();
    size_ = init.size();
    return *this;
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::begin() noexcept
  {
    return data_.begin();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::const_iterator Dictionary< Key, Value, Compare >::begin() const noexcept
  {
    return cbegin();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::const_iterator Dictionary< Key, Value, Compare >::cbegin() const noexcept
  {
    return data_.cbegin();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::end() noexcept
  {
    return data_.end();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::const_iterator Dictionary< Key, Value, Compare >::end() const noexcept
  {
    return cend();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::const_iterator Dictionary< Key, Value, Compare >::cend() const noexcept
  {
    return data_.cend();
  }

  template< typename Key, typename Value, typename Compare >
  bool Dictionary< Key, Value, Compare >::empty() const noexcept
  {
    return cbegin() == cend();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::size_type Dictionary< Key, Value, Compare >::size() const noexcept
  {
    return size_;
  }

  template< typename Key, typename Value, typename Compare >
  void Dictionary< Key, Value, Compare >::clear() noexcept
  {
    data_.clear();
    size_ = 0;
  }

  template< typename Key, typename Value, typename Compare >
  void Dictionary< Key, Value, Compare >::swap(this_t & other)
  {
    data_.swap(other.data_);
    std::swap(comp_, other.comp_);
    std::swap(size_, other.size_);
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::const_iterator Dictionary< Key, Value, Compare >::lower_bound(const key_type & key) const
  {
    auto res = before_begin();
    for (auto it = begin(); it != end() && key_comp()(it->first, key); ++it, ++res)
    {}
    return res;
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::lower_bound(const key_type & key)
  {
    const_iterator cit = (static_cast< const this_t & >(*this)).lower_bound(key);
    return data_.erase_after(cit, cit);
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::const_iterator Dictionary< Key, Value, Compare >::upper_bound(const key_type & key) const
  {
    auto res = before_begin();
    for (auto it = begin(); it != end() && !key_comp()(it->first, key); ++it, ++res)
    {}
    return res;
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::upper_bound(const key_type & key)
  {
    const_iterator cit = (static_cast< const this_t & >(*this)).upper_bound(key);
    return data_.erase_after(cit, cit);
  }

  template< typename Key, typename Value, typename Compare >
  std::pair<
      typename Dictionary< Key, Value, Compare >::iterator,
      typename Dictionary< Key, Value, Compare >::iterator
  > Dictionary< Key, Value, Compare >::equal_range(const key_type & key)
  {
    return std::pair< iterator, iterator >(lower_bound(key), ++(upper_bound(key)));
  }

  template< typename Key, typename Value, typename Compare >
  std::pair<
      typename Dictionary< Key, Value, Compare >::const_iterator,
      typename Dictionary< Key, Value, Compare >::const_iterator
  > Dictionary< Key, Value, Compare >::equal_range(const key_type & key) const
  {
    return std::pair< iterator, iterator >(lower_bound(key), ++(upper_bound(key)));
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::const_iterator Dictionary< Key, Value, Compare >::find(const key_type & key) const
  {
    const_iterator cit = lower_bound(key);
    const_iterator moved_cit = cit;
    ++moved_cit;
    if (moved_cit == end())
    {
      return clast();
    }
    key_compare compare = key_comp();
    return (!compare(moved_cit->first, key) && !compare(key, moved_cit->first)) ? cit : clast();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::find(const key_type & key)
  {
    const_iterator cit = (static_cast< const this_t & >(*this)).find(key);
    return data_.erase_after(cit, cit);
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::size_type Dictionary< Key, Value, Compare >::count(const key_type & key) const
  {
    return ++(find(key)) == end() ? 0ull : 1ull;
  }

  template< typename Key, typename Value, typename Compare >
  const Value & Dictionary< Key, Value, Compare >::at(const key_type & key) const
  {
    const_iterator it = find(key);
    if (++it == cend())
    {
      throw std::out_of_range("There is no such key");
    }
    return it->second;
  }

  template< typename Key, typename Value, typename Compare >
  Value & Dictionary< Key, Value, Compare >::at(const key_type & key)
  {
    return const_cast< Value & >((static_cast< const this_t & >(*this)).at(key));
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::before_begin() noexcept
  {
    return data_.before_begin();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::const_iterator Dictionary< Key, Value, Compare >::before_begin() const noexcept
  {
    return cbefore_begin();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::const_iterator Dictionary< Key, Value, Compare >::cbefore_begin() const noexcept
  {
    return data_.cbefore_begin();
  }

  template< typename Key, typename Value, typename Compare >
  std::pair<
      typename Dictionary< Key, Value, Compare >::iterator,
      bool
  > Dictionary< Key, Value, Compare >::insert(const value_type & value)
  {
    iterator it = lower_bound(value.first);
    iterator moved_it = it;
    ++moved_it;
    if (moved_it == end())
    {
      return {data_.insert_after(it, value), true};
    }
    if (moved_it->first == value.first)
    {
      moved_it->second = value.second;
      return {moved_it, false};
    }
    return {data_.insert_after(it, value), true};
  }

  template< typename Key, typename Value, typename Compare >
  template< typename P >
  std::pair< typename Dictionary< Key, Value, Compare >::iterator, bool > Dictionary< Key, Value, Compare >::insert(P && value)
  {
    static_assert(std::is_constructible< value_type, P&& >::value, "Value type isn't constructible from type you try to insert");
    const value_type temp(std::forward< P >(value));
    return insert(temp);
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iterator
      Dictionary< Key, Value, Compare >::insert(const_iterator pos, const value_type & value)
  {
    Compare comp = key_comp();
    const_iterator moved_pos = pos;
    ++moved_pos;
    if (comp(pos->first, value) && comp(value, moved_pos->first))
    {
      return data_.insert_after(pos, value);
    }
    return (insert(value)).first;
  }

  template< typename Key, typename Value, typename Compare >
  template< typename P >
  typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::insert(const_iterator pos, P && value)
  {
    static_assert(std::is_constructible< value_type, P&& >::value, "Value type isn't constructible from type you try to insert");
    const value_type temp(std::forward< P >(value));
    return insert(pos, temp);
  }

  template< typename Key, typename Value, typename Compare >
  template< typename InputIt >
  void Dictionary< Key, Value, Compare >::insert(InputIt first, InputIt last)
  {
    for (; first != last; ++first)
    {
      insert(*first);
    }
  }

  template< typename Key, typename Value, typename Compare >
  void Dictionary< Key, Value, Compare >::insert(std::initializer_list< value_type > init)
  {
    insert(init.begin(), init.end());
  }

  template< typename Key, typename Value, typename Compare >
  template< typename... Args >
  std::pair<
      typename Dictionary< Key, Value, Compare >::iterator,
      bool
  > Dictionary< Key, Value, Compare >::emplace(Args && ... args)
  {
    return insert(value_type(std::forward< Args >(args)...));
  }

  template< typename Key, typename Value, typename Compare >
  template< typename... Args >
  typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::emplace(const_iterator pos, Args && ... args)
  {
    return insert(pos, value_type(std::forward< Args >(args)...));
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::erase_after(const_iterator pos)
  {
    return data_.erase_after(pos);
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iterator
      Dictionary< Key, Value, Compare >::erase_after(const_iterator first, const_iterator last)
  {
    return data_.erase_after(first, last);
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::size_type Dictionary< Key, Value, Compare >::erase(const key_type & key)
  {
    iterator it = find(key);
    if (it == last())
    {
      return 0ull;
    }
    erase_after(it);
    return 1ull;
  }

  template< typename Key, typename Value, typename Compare >
  Value & Dictionary< Key, Value, Compare >::operator[](const key_type & key)
  {
    try
    {
      return at(key);
    }
    catch (const std::out_of_range & e)
    {}
    return (*(emplace(key, mapped_type{}).first)).second;
  }

  template< typename Key, typename Value, typename Compare >
  Value & Dictionary< Key, Value, Compare >::operator[](key_type && key)
  {
    return (*this)[key];
  }

  template< typename Key, typename Value, typename Compare >
  bool Dictionary< Key, Value, Compare >::isEqualTo(const this_t & other) const noexcept
  {
    return size_ == other.size_ && data_ == other.data_;
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::last() noexcept
  {
    return data_.last();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::const_iterator Dictionary< Key, Value, Compare >::last() const noexcept
  {
    return clast();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::const_iterator Dictionary< Key, Value, Compare >::clast() const noexcept
  {
    return data_.clast();
  }

  template< typename Key, typename Value, typename Compare >
  class Dictionary< Key, Value, Compare >::value_compare
  {
   public:
    using result_type = bool;
    using first_argument_type = value_type;
    using second_argument_type = value_type;
    bool operator()(const value_type & lhs, const value_type & rhs) const
    {
      return comp(lhs.first, rhs.first);
    };
   protected:
    Compare comp;
    explicit value_compare(Compare c): comp(c) {};
  };

  template< typename Key, typename Value, typename Compare >
  bool operator==(const Dictionary< Key, Value, Compare > & lhs, const Dictionary< Key, Value, Compare > & rhs)
  {
    return lhs.isEqualTo(rhs);
  }

  template< typename Key, typename Value, typename Compare >
  bool operator!=(const Dictionary< Key, Value, Compare > & lhs, const Dictionary< Key, Value, Compare > & rhs)
  {
    return !(lhs == rhs);
  }
}

#endif
