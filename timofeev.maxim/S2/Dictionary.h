#ifndef DICTIONARY_H
#define DICTIONARY_H
#include "ForwardList.h"
namespace timofeev
{
  template< typename Key, typename Value, typename Compare = std::less< Key > >
  class Dictionary
  {
  public:
    using value_type = std::pair< const Key, Value >;
    using iter = ForwardIterator< value_type >;
    using constIter = ForwardConstIterator< value_type >;

    void push(Key k, Value v);

    Dictionary();
    ~Dictionary() = default;

    Dictionary(const Dictionary &other);
    Dictionary(Dictionary &&other) noexcept;

    Dictionary< Key, Value, Compare > &operator=(const Dictionary &other);
    Dictionary< Key, Value, Compare > &operator=(Dictionary &&other) noexcept;

    Value &at(const Key &key);
    const Value& at(const Key& key) const;
    Value& operator[](Key&& key);
    Value &operator[](const Key &key);

    iter begin();
    constIter begin() const;
    constIter cbegin() const noexcept;

    iter end();
    constIter end() const;
    constIter cend() const noexcept;

    iter insert(value_type &&value);
    iter insert(const value_type &value);
    iter insert( constIter pos, const value_type& value ); //
    template< class P >
    iter insert( constIter pos, P&& value );
    template< typename InputIt >
    void insert(InputIt first, InputIt last);

    iter erase(iter pos);
    iter erase(constIter pos);
    iter erase(iter first, iter last);
    iter erase(constIter first, constIter last);

    void swap(Dictionary< Key, Value, Compare > &other) noexcept;

    size_t count(const Key &key) const;
    iter find(const Key &key);
    constIter find(const Key &key) const;
    bool contains(const Key &key) const;

    bool empty() const noexcept;
    size_t size() const noexcept;
    void clear();

  private:
    ForwardList< value_type > data_;
    Compare compare_;
    size_t size_d;
  };

  template< typename Key, typename Value, typename Compare >
  template< typename P >
  typename Dictionary< Key, Value, Compare >::iter Dictionary<Key, Value, Compare >::insert(constIter it, P &&value)
  {
    auto existing = find(value.first);
    if (existing != end())
    {
      return existing;
    }
    else
    {
      auto inserted = data_.insert(it.current(), std::forward<P>(value));
      size_d++;
      return typename Dictionary< Key, Value, Compare >::iter(inserted);
    }
  }
  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iter Dictionary<Key, Value,
    Compare>::insert(Dictionary::constIter pos, const value_type &value)
  {
    auto existing = find(value.first);
    if (existing != end())
    {
      return existing;
    }
    else
    {
      auto inserted = data_.insert(pos.current(), value);
      size_d++;
      return typename Dictionary< Key, Value, Compare >::iter(inserted);
    }
  }

  template< typename Key, typename Value, typename Compare >
  Value &Dictionary< Key, Value, Compare >::operator[](const Key &key)
  {
    try
    {
      return at(key);
    }
    catch (const std::out_of_range &e)
    {
      value_type newValue = std::make_pair(key, Value{});
      data_.push_front(newValue);
      size_d++;
      return data_.front().second;
    }
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iter Dictionary< Key, Value,
    Compare >::erase(constIter first, constIter last)
  {
    return erase(constIter(first), constIter(last));
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iter Dictionary< Key, Value,
    Compare >::erase(iter first, iter last)
  {
    while(first != last)
    {
      erase(first);
      first++;
      size_d--;
    }
    return iter(last.node_);
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iter Dictionary< Key, Value,
    Compare >::erase(Dictionary::constIter pos)
  {
    return erase(constIter(pos));
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iter Dictionary< Key, Value,
    Compare >::erase(iter pos)
  {
    if (pos == end())
    {
      return end();
    }
    auto prev = begin();
    auto cur = ++begin();
    while (cur != end())
    {
      if (cur == pos)
      {
        size_d--;
        return data_.erase_after(prev);
      }
      cur++;
      prev++;
    }
    return end();
  }

  template< typename Key, typename Value, typename Compare >
  template<typename InputIt>
  void Dictionary< Key, Value, Compare >::insert(InputIt first, InputIt last)
  {
    for (auto it = first; it != last; ++it)
    {
      insert(*it);
    }
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iter Dictionary< Key, Value, Compare >::insert(const value_type &value)
  {
    if (begin() == end())
    {
      data_.push_front(value);
      size_d++;
      return begin();
    }
    else
    {
      auto it = find(value.first);
      if (it == end())
      {
        data_.pushBack(value);
        size_d++;
        return begin();
      }
      else
      {
        it->second = value.second;
        return it;
      }
    }
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iter Dictionary< Key, Value, Compare >::insert(value_type &&value)
  {
    return insert(value);
  }

  template< typename Key, typename Value, typename Compare >
  void Dictionary< Key, Value, Compare >::push(Key k, Value v)
  {
    insert(value_type(k, v));
  }

  template< typename Key, typename Value, typename Compare >
  Value &Dictionary< Key, Value, Compare >::operator[](Key &&key)
  {
    return (*this)[key];
  }

  template< typename Key, typename Value, typename Compare>
  const Value &Dictionary< Key, Value, Compare >::at(const Key &key) const
  {
    for (auto it = cbegin(); it != cend(); it++)
    {
      if (!compare_(it->first, key) && !compare_(key, it->first))
      {
        return it->second;
      }
      else if (it == cend())
      {
        throw std::out_of_range("Out of range");
      }
    }
  }

  template< typename Key, typename Value, typename Compare >
  Value &Dictionary< Key, Value, Compare >::at(const Key &key)
  {
    iter it = find(key);
    if (it == end())
    {
      throw std::out_of_range("no Key");
    }
    return it->second;
  }

  template< typename Key, typename Value, typename Compare >
  bool Dictionary< Key, Value, Compare >::contains(const Key &key) const
  {
    return count(key) > 0;
  }

  template< typename Key, typename Value, typename Compare >
  size_t Dictionary< Key, Value, Compare >::count(const Key &key) const
  {
    auto it = find(key);
    return (it != end()) ? 1ull : 0ull;
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::constIter Dictionary< Key, Value, Compare >::find(const Key &key) const
  {
    auto it = begin();
    while (it != end())
    {
      if (!compare_(it->first, key) && !compare_(key, it->first))
      {
        return it;
      }
      ++it;
    }
    return cend();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iter Dictionary< Key, Value, Compare >::find(const Key &key)
  {
    auto it = begin();
    while (it != end())
    {
      if (!compare_(it->first, key) && !compare_(key, it->first))
      //if (compare_(it->first, key) || compare_(key, it->first))
      {
        return it;
      }
      ++it;
    }
    return end();
  }

  template< typename Key, typename Value, typename Compare >
  void Dictionary< Key, Value, Compare >::swap(Dictionary< Key, Value, Compare > &other) noexcept
  {
    std::swap(data_, other.data_);
    std::swap(compare_, other.compare_);
    std::swap(size_d, other.size_d);
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::constIter Dictionary< Key, Value, Compare >::cend() const noexcept
  {
    return data_.cend();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::constIter Dictionary< Key, Value, Compare >::end() const
  {
    return cend();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iter Dictionary< Key, Value, Compare >::end()
  {
    return data_.end();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::constIter Dictionary< Key, Value, Compare >::cbegin() const noexcept
  {
    return data_.cbegin();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::constIter Dictionary< Key, Value, Compare >::begin() const
  {
    return cbegin();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iter Dictionary< Key, Value, Compare >::begin()
  {
    return data_.begin();
  }


  template< typename Key, typename Value, typename Compare >
  bool  Dictionary< Key, Value, Compare >::empty() const noexcept
  {
    return data_.empty();
  }

  template< typename Key, typename Value, typename Compare >
  size_t Dictionary< Key, Value, Compare >::size() const noexcept
  {
    return size_d;
  }

  template< typename Key, typename Value, typename Compare >
  void Dictionary< Key, Value, Compare >::clear()
  {
    data_.Fclear();
    size_d = 0;
  }

  template<typename Key, typename Value, typename Compare>
  Dictionary<Key, Value, Compare> &Dictionary<Key, Value, Compare>::operator=(Dictionary &&other) noexcept
  {
    if (this != &other)
    {
      *this = other;
    }
    return *this;
  }

  template<typename Key, typename Value, typename Compare>
  Dictionary<Key, Value, Compare> &Dictionary<Key, Value, Compare>::operator=(const Dictionary &other)
  {
    if (this != std::addressof(other))
    {
      data_ = other.data_;
      compare_ = other.compare_;
      size_d = other.size_d;
    }
    return *this;
  }

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare >::Dictionary(Dictionary &&other) noexcept:
    data_(std::move(other.data_)),
    compare_(std::move(other.compare_)),
    size_d(other.size_d)
  {
    other.size_d = 0;
  }

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare >::Dictionary(const Dictionary &other):
    data_(other.data_),
    compare_(other.compare_),
    size_d(other.size_d)
  {}

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare >::Dictionary():
    data_(),
    compare_(),
    size_d(0)
  {}
}
#endif
