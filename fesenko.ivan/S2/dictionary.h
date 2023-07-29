#ifndef DICTIONARY_H
#define DICTIONARY_H
#include "forwardList.h"

namespace fesenko
{
  template< typename Key, typename Value, typename Compare >
  class Dictionary
  {
   public:
    using key_type = Key;
    using mapped_type = Value;
    using value_type = std::pair< const key_type, mapped_type >;
    using key_compare = Compare;
    using reference = value_type &;
    using const_reference = const value_type &;
    using pointer = value_type *;
    using const_pointer = const value_type *;
    using iterator = typename ForwardList< value_type >::iterator;
    using const_iterator = typename ForwardList< value_type >::const_iterator;
    using difference_type = std::ptrdiff_t;
    using size_type = std::size_t;
    using this_t = Dictionary< Key, Value, Compare >;
    class value_compare;
    Dictionary();
    explicit Dictionary(const key_compare &);
    Dictionary(const this_t &);
    Dictionary(this_t &&);
    ~Dictionary() = default;
    this_t &operator=(const this_t &);
    this_t &operator=(this_t &&);
    iterator before_begin() noexcept;
    const_iterator before_begin() const noexcept;
    const_iterator cbefore_begin() const noexcept;
    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;
    bool empty() const noexcept;
    size_type size() const noexcept;
    mapped_type &operator[](const key_type &);
    mapped_type &operator[](key_type &&);
    mapped_type &at(const key_type &);
    const mapped_type &at(const key_type &) const;
    std::pair< iterator, bool > insert(const value_type &);
    template< typename P >
    std::pair< iterator, bool > insert(P &&);
    iterator insert(const_iterator, const value_type &);
    template< typename P >
    iterator insert(const_iterator, P &&);
    template< typename InputIterator >
    void insert(InputIterator, InputIterator);
    iterator erase_after(const_iterator);
    iterator erase_after(const_iterator, const_iterator);
    void swap(this_t &);
    void clear() noexcept;
    key_compare key_comp() const;
    value_compare value_comp() const;
    iterator find(const key_type &);
    const_iterator find(const key_type &) const;
   private:
    ForwardList< value_type > list_;
    Compare comp_;
    size_type size_;
  };

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare >::Dictionary():
    list_(),
    comp_(),
    size_(0)
  {}

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare >::Dictionary(const key_compare &comp):
    list_(),
    comp_(comp),
    size_(0)
  {}

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare >::Dictionary(const this_t &other):
    list_(other.list_),
    comp_(other.comp_),
    size_(other.size_)
  {}

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare >::Dictionary(this_t &&other):
    list_(std::move(other.list_)),
    comp_(std::move(other.comp_)),
    size_(other.size_)
  {
    other.size_ = 0;
  }

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare > &Dictionary< Key, Value, Compare >::operator=(const this_t &other)
  {
    if (this != std::addressof(other)) {
      Compare temp = other.comp_;
      list_ = other.list_;
      comp_ = std::move(temp);
      size_ = other.size_;
    }
    return *this;
  }

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare > &Dictionary< Key, Value, Compare >::operator=(this_t &&other)
  {
    if (this != std::addressof(other)) {
      list_ = std::move(other.list_);
      comp_ = std::move(other.comp_);
      size_ = other.size_;
      other.size_ = 0;
    }
    return *this;
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::begin() noexcept
  {
    return list_.begin();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::const_iterator Dictionary< Key, Value, Compare >::begin() const noexcept
  {
    return cbegin();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::const_iterator Dictionary< Key, Value, Compare >::cbegin() const noexcept
  {
    return list_.cbegin();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::end() noexcept
  {
    return list_.end();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::const_iterator Dictionary< Key, Value, Compare >::end() const noexcept
  {
    return cend();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::const_iterator Dictionary< Key, Value, Compare >::cend() const noexcept
  {
    return list_.cend();
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
  const Value &Dictionary< Key, Value, Compare >::at(const key_type &key) const
  {
    const_iterator cit = find(key);
    if (cit++ == cend()) {
      throw std::out_of_range("There is no such key");
    }
    return cit->second;
  }

  template< typename Key, typename Value, typename Compare >
  Value &Dictionary< Key, Value, Compare >::at(const key_type &key)
  {
    return const_cast< Value & >((static_cast< const this_t & >(*this)).at(key));
  }

  template< typename Key, typename Value, typename Compare >
  Value &Dictionary< Key, Value, Compare >::operator[](const key_type &key)
  {
    try {
      return at(key);
    } catch (const std::out_of_range &e) {
    }
    return (*((this->insert(std::make_pair(key, mapped_type()))).first));
  }

  template< typename Key, typename Value, typename Compare >
  Value &Dictionary< Key, Value, Compare >::operator[](key_type &&key)
  {
    return (*this)[key];
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::const_iterator Dictionary< Key, Value, Compare >::find(const key_type &key) const
  {
    Compare comp = key_comp();
    const_iterator cur = cbegin();
    while (cur->next != cend()) {
      if (!comp(cur->first, key) && !comp(key, cur->first)) {
        break;
      }
      cur++;
    }
    return cur;
  }

  template< typename Key, typename Value, typename Compare >
  std::pair<
      typename Dictionary< Key, Value, Compare >::iterator,
      bool
  > Dictionary< Key, Value, Compare >::insert(const value_type &value)
  {
    Compare comp = key_comp();
    iterator cur = cbegin();
    while (cur->next != cend()) {
      if (!comp(cur->first, value.first)) {
        if (comp(value.first, cur->first)) {
          return {list_.insert_after(cur, value), true};
        }
        break;
      }
      cur++;
    }
    return {cur, false};
  }

  template< typename Key, typename Value, typename Compare >
  template< typename P >
  std::pair<
      typename Dictionary< Key, Value, Compare >::iterator,
      bool
  > Dictionary< Key, Value, Compare >::insert(P &&value)
  {
    static_assert(std::is_constructible< value_type, P && >::value, "Can`t construct value type");
    const value_type temp(std::forward< P >(value));
    return insert(temp);
  }

template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iterator
      Dictionary< Key, Value, Compare >::insert(const_iterator pos, const value_type &value)
  {
    Compare comp = key_comp();
    const_iterator cur = pos;
    cur++;
    if (comp(pos->first, value.first) && comp(value.first, cur->first)) {
      return list_.insert_after(pos, value);
    }
    return (insert(value)).first;
  }

  template< typename Key, typename Value, typename Compare >
  template< typename P >
  typename Dictionary< Key, Value, Compare >::iterator
      Dictionary< Key, Value, Compare >::insert(const_iterator pos, P &&value)
  {
    static_assert(std::is_constructible< value_type, P&& >::value, "Can`t construct value type");
    const value_type temp(std::forward< P >(value));
    return insert(pos, temp);
  }

  template< typename Key, typename Value, typename Compare >
  template< typename InputIt >
  void Dictionary< Key, Value, Compare >::insert(InputIt first, InputIt last)
  {
    for (; first != last; first++) {
      insert(*first);
    }
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::erase_after(const_iterator pos)
  {
    return list_.erase_after(pos);
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iterator
      Dictionary< Key, Value, Compare >::erase_after(const_iterator first, const_iterator last)
  {
    return list_.erase_after(first, last);
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::find(const key_type &key)
  {
    return (static_cast< const this_t & >(*this)).find(key);
  }

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
  class Dictionary< Key, Value, Compare >::value_compare
  {
   public:
    bool operator()(const value_type &lhs, const value_type &rhs) const
    {
      return comp(lhs.first, rhs.first);
    };
   protected:
    Compare comp;
    explicit value_compare(Compare c): comp(c) {};
  };

}
#endif
