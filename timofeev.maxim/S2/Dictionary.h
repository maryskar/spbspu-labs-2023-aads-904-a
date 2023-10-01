#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <functional>
#include <utility>
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

    Dictionary();
    Dictionary(const Dictionary< Key, Value, Compare > &other);
    Dictionary(Dictionary< Key, Value, Compare > &&other);
    ~Dictionary() = default;

    Dictionary< Key, Value, Compare > &operator=(const Dictionary< Key, Value, Compare > &other);
    Dictionary< Key, Value, Compare > &operator=(Dictionary< Key, Value, Compare > &&other);

    Value &at(const Key &key);
    const Value &at(const Key &key) const;
    Value &operator[](const Key &key);
    Value &operator[](Key &&key);

    iter begin() noexcept;
    constIter begin() const noexcept;
    constIter cbegin() const noexcept;
    iter end() noexcept;
    constIter end() const noexcept;
    constIter cend() const noexcept;

    std::pair< iter, bool > insert(const value_type &value);
    std::pair< iter, bool > insert(const value_type &&value);
    iter insert(value_type &&value);
    iter insert(constIter pos, const value_type &value );
    template< typename P >
    std::pair< iter, bool > insert(P &&value);
    template< typename P >
    iter insert(constIter pos, P &&value );
    template< typename Input >
    void insert(Input first, Input last);

    iter erase(iter pos);
    iter erase(constIter pos);
    iter erase(iter first, iter last);
    iter erase(constIter first, constIter last);

    bool empty() const noexcept;
    size_t size() const noexcept;
    void clear();

    void swap(Dictionary< Key, Value, Compare > &other);

    iter find(const Key &key);
    constIter find(const Key &key) const;
    size_t count(const Key &key) const;
    bool contains(const Key &key) const;

    void push(Key k, Value v);
  private:
    ForwardList< value_type > data_;
    Compare compare_;
    size_t size_;
  };

  template<typename Key, typename Value, typename Compare>
  void Dictionary<Key, Value, Compare>::push(Key k, Value v)
  {
    insert(std::make_pair(k,v));
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iter Dictionary< Key, Value,
    Compare >::erase(constIter first, constIter last)
  {
    return erase(constIter(first), constIter(last));
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iter Dictionary< Key, Value,
    Compare >::erase(Dictionary::constIter pos)
  {
    return erase(constIter(pos));
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iter Dictionary< Key, Value,
    Compare >::erase(iter first, iter last)
  {
    while(first != last)
    {
      erase(first);
      first++;
      size_--;
    }
    return iter(last.node_);
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
        size_--;
        return data_.erase_after(prev);
      }
      cur++;
      prev++;
    }
    return end();
  }

  template< typename Key, typename Value, typename Compare >
  Value &Dictionary< Key, Value, Compare >::operator[](const Key &key)
  {
    for(auto it = data_.begin(); it != data_.end(); ++it) {
      if(it->first == key) {
        return it->second;
      }
    }
    value_type newValue = std::make_pair(key, Value{});
    data_.push_front(newValue);
    size_++;
    return data_.front().second;
  }

  template< typename Key, typename Value, typename Compare >
  Value &Dictionary< Key, Value, Compare >::operator[](Key &&key)
  {
    return (*this)[key];
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iter Dictionary< Key, Value,
    Compare >::begin() noexcept
  {
    return data_.begin();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::constIter Dictionary< Key, Value,
    Compare >::cbegin() const noexcept
  {
    return data_.cbegin();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::constIter Dictionary< Key, Value,
    Compare >::begin() const noexcept
  {
    return cbegin();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iter Dictionary< Key, Value,
    Compare >::end() noexcept
  {
    return data_.end();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::constIter Dictionary< Key, Value,
    Compare >::cend() const noexcept
  {
    return data_.cend();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::constIter Dictionary< Key, Value,
    Compare >::end() const noexcept
  {
    return cend();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::constIter Dictionary< Key, Value,
    Compare >::find(const Key &key) const
  {
    for(auto it = data_.cbegin(); it != data_.cend(); ++it)
    {
      if (!(compare_(it->first, key)) && !(compare_(key, it->first)))
      {
        return it;
      }
    }
    return data_.cend();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iter Dictionary< Key, Value,
    Compare >::find(const Key &key)
  {
    for(auto it = data_.begin(); it != data_.end(); ++it)
    {
      if (!(compare_(it->first, key)) && !(compare_(key, it->first)))
      {
        return it;
      }
    }
    return data_.end();
  }

  template< typename Key, typename Value, typename Compare >
  Value & Dictionary< Key, Value, Compare >::at(const Key &key)
  {
    auto it = find(key);
    if (it == data_.end())
    {
      throw std::invalid_argument("invalid_argument");
    }
    return it->second;
  }

  template< typename Key, typename Value, typename Compare >
  const Value & Dictionary< Key, Value, Compare >::at(const Key &key) const
  {
    return const_cast< Dictionary< Key, Value, Compare >* >(this)->at(key);
  }

  template< typename Key, typename Value, typename Compare >
  bool Dictionary< Key, Value, Compare >::empty() const noexcept
  {
    return data_.empty();
  }

  template< typename Key, typename Value, typename Compare >
  size_t Dictionary< Key, Value, Compare >::size() const noexcept
  {
    return size_;
  }

  template< typename Key, typename Value, typename Compare >
  void Dictionary< Key, Value, Compare >::clear()
  {
    data_.clear();
    size_ = 0;
  }

  template< typename Key, typename Value, typename Compare >
  void Dictionary< Key, Value, Compare >::swap(Dictionary< Key, Value, Compare > &other)
  {
    std::swap(data_, other.data_);
    std::swap(compare_, other.compare_);
    size_ = other.size_;
    other.size_ = 0;
  }

  template< typename Key, typename Value, typename Compare >
  size_t Dictionary< Key, Value, Compare >::count(const Key & key) const
  {
    auto it = find(key);
    return (it != end()) ? 1ull : 0ull;
  }

  template< typename Key, typename Value, typename Compare >
  bool Dictionary< Key, Value, Compare >::contains(const Key &key) const
  {
    return count(key);
  }

  template< typename Key, typename Value, typename Compare >
  std::pair< typename Dictionary< Key, Value, Compare >::iter,
    bool > Dictionary< Key, Value, Compare >::insert(const value_type &&value)
  {
    return insert(std::make_pair(std::move(value)));
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iter Dictionary< Key, Value,
    Compare >::insert(value_type &&value)
  {
    return insert(value);
  }

  template< typename Key, typename Value, typename Compare >
  std::pair< typename Dictionary< Key, Value, Compare >::iter,
    bool > Dictionary< Key, Value, Compare >::insert(const value_type &value)
  {
    iter cur = data_.before_begin();
    for (iter tmp = begin(); tmp != end(); tmp++)
    {
      if (!compare_(value.first, tmp->first) && !compare_(tmp->first, value.first))
      {
        return std::make_pair(tmp, false);
      }
      else if (compare_(value.first, tmp->first))
      {
        iter inserted = data_.insert_after(cur, value);
        size_++;
        return std::make_pair(inserted, true);
      }
      cur++;
    }
    iter res = data_.insert_after(cur, value);
    size_++;
    return std::make_pair(res, true);
  }

  template< typename Key, typename Value, typename Compare >
  template< typename P >
  typename Dictionary< Key, Value, Compare >::iter Dictionary< Key, Value,
    Compare >::insert(constIter pos, P &&value)
  {
    const value_type tmp(std::forward< P >(value));
    return insert(pos, tmp);
  }

  template< typename Key, typename Value, typename Compare >
  template< typename P >
  std::pair< typename Dictionary< Key, Value, Compare >::iter, bool >
  Dictionary<Key, Value, Compare>::insert(P &&value)
  {
    iter cur = data_.before_begin();
    for (iter tmp = begin(); tmp != end(); tmp++)
    {
      if (!compare_(value.first, tmp->first) && !compare_(tmp->first, value.first))
      {
        return std::make_pair(tmp, false);
      }
      else if (compare_(value.first, tmp->first))
      {
        iter inserted = data_.insert_after(cur, value);
        size_++;
        return std::make_pair(inserted, true);
      }
      cur++;
    }
    iter res = data_.insert_after(cur, value);
    size_++;
    return std::make_pair(res, true);
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iter
  Dictionary< Key, Value, Compare >::insert(constIter pos, const value_type &value)
  {
    auto it = find(value.first);
    if (it != end())
    {
      return it;
    }
    else
    {
      auto tmp = data_.insert(pos.node_, value);
      size_++;
      return iter(tmp);
    }
  }

  template< typename Key, typename Value, typename Compare >
  template< typename Input >
  void Dictionary< Key, Value, Compare >::insert(Input first, Input last)
  {
    auto it = first;
    for (; it != last; ++it)
    {
      insert(*it);
    }
  }
  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare >::Dictionary(const Dictionary< Key, Value, Compare > &other):
    data_(other.data_),
    compare_(other.compare_),
    size_(other.size())
  {}

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare >::Dictionary(Dictionary< Key, Value, Compare > &&other):
    data_(std::move(other.data_)),
    compare_(std::move(other.compare_)),
    size_(other.size_)
  {
    other.size_ = 0;
  }

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare > & Dictionary< Key, Value,
    Compare >::operator=(const Dictionary< Key, Value, Compare > &other)
  {
    if (this != &other)
    {
      data_ = other.data_;
      compare_ = other.compare_;
      size_ = other.size_;
    }
    return *this;
  }

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare > & Dictionary< Key, Value,
    Compare >::operator=(Dictionary< Key, Value, Compare > &&other)
  {
    if (this != &other)
    {
      data_ = std::move(other.data_);
      compare_ = std::move(other.compare_);
      size_ = other.size_;
      other.size_ = 0;
    }
    return *this;
  }

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare >::Dictionary():
    data_(),
    compare_(Compare()),
    size_(0)
  {}

}
#endif
