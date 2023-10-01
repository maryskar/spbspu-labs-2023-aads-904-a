#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <functional>
#include <utility>
#include "forwardList.h"

namespace aksenov
{
  template< typename Key, typename T, typename Compare = std::less< Key > >
  class Dictionary
  {
  public:
    using keyType = Key;
    using mappedType = T;
    using valueType = std::pair< const Key, T >;
    using sizeType = std::size_t;
    using difference_type = std::ptrdiff_t;
    using keyCompare = Compare;
    using reference = valueType &;
    using constReference = const valueType &;
    using pointer = valueType *;
    using constPointer = const valueType *;
    using iterator = typename ForwardList< valueType >::iterator;
    using constIterator = typename ForwardList< valueType >::constIterator;
    using thisT = Dictionary< Key, T, Compare >;

    Dictionary();
    Dictionary(const Dictionary< Key, T, Compare > &other);
    Dictionary(Dictionary< Key, T, Compare > &&other);
    ~Dictionary() = default;

    thisT &operator=(const thisT &other);
    thisT &operator=(thisT &&other);
    mappedType &operator[](const Key &key);
    mappedType &operator[](Key &&key);

    iterator begin() noexcept;
    constIterator begin() const noexcept;
    constIterator cbegin() const noexcept;
    iterator end() noexcept;
    constIterator end() const noexcept;
    constIterator cend() const noexcept;
    iterator find(const Key &key);
    constIterator find(const Key &key) const;
    constIterator eraseAfter(constIterator pos);
    constIterator eraseAfter(constIterator first, constIterator last);
    iterator last() noexcept;
    constIterator last() const noexcept;
    constIterator clast() const noexcept;


    mappedType &at(const Key &key);
    const mappedType &at(const Key &key) const;
    bool isEmpty() const noexcept;
    sizeType size() const noexcept;
    void clear();
    void swap(thisT &other);
    sizeType count(const keyType &key) const;
    bool contains(const Key &key) const;
    std::pair< iterator, bool > insert(const valueType &value);
    std::pair< iterator, bool > insert(const valueType &&value);
    void insert(const Key &key, const T &value);
    template< typename P >
    std::pair< iterator, bool > insert(P &&value);
    iterator insert(constIterator it, const valueType &value);
    template< typename P >
    iterator insert(constIterator, P &&value);
    template< typename InputIterator >
    void insert(InputIterator, InputIterator);
    keyCompare keyComp() const;
  private:
    ForwardList< valueType > data_;
    Compare comp_;
    sizeType size_;
  };

  template< typename Key, typename T, typename Compare >
  Dictionary< Key, T, Compare >::Dictionary():
    data_(),
    comp_(Compare()),
    size_(0)
  {}

  template< typename Key, typename T, typename Compare >
  Dictionary< Key, T, Compare >::Dictionary(const Dictionary< Key, T, Compare > &other):
    data_(other.data_),
    comp_(other.comp_),
    size_(other.size())
  {}

  template< typename Key, typename T, typename Compare >
  Dictionary< Key, T, Compare >::Dictionary(Dictionary< Key, T, Compare > &&other):
    data_(std::move(other.data_)),
    comp_(std::move(other.comp_)),
    size_(other.size_)
  {
    other.size_ = 0;
  }

  template< typename Key, typename T, typename Compare >
  Dictionary< Key, T, Compare > & Dictionary< Key, T, Compare >::operator=(const thisT &other)
  {
    if (this != &other)
    {
      data_ = other.data_;
      comp_ = other.comp_;
      size_ = other.size_;
    }
    return *this;
  }

  template< typename Key, typename T, typename Compare >
  Dictionary< Key, T, Compare > & Dictionary< Key, T, Compare >::operator=(thisT &&other)
  {
    if (this != &other)
    {
      data_ = std::move(other.data_);
      comp_ = std::move(other.comp_);
      size_ = other.size_;
      other.size_ = 0;
    }
    return *this;

  }

  template< typename Key, typename T, typename Compare >
  T &Dictionary< Key, T, Compare >::operator[](const Key &key)
  {
    auto resultPair = this->insert(std::make_pair(key, T{}));
    return resultPair.first->second;
  }

  template< typename Key, typename T, typename Compare >
  T &Dictionary< Key, T, Compare >::operator[](Key &&key)
  {
    return (*this)[key];
  }

  template< typename Key, typename T, typename Compare >
  typename Dictionary< Key, T, Compare >::iterator Dictionary< Key, T, Compare >::begin() noexcept
  {
    return data_.begin();
  }

  template< typename Key, typename T, typename Compare >
  typename Dictionary< Key, T, Compare >::constIterator Dictionary< Key, T, Compare >::cbegin() const noexcept
  {
    return data_.cbegin();
  }

  template< typename Key, typename T, typename Compare >
  typename Dictionary< Key, T, Compare >::constIterator Dictionary< Key, T, Compare >::begin() const noexcept
  {
    return cbegin();
  }

  template< typename Key, typename T, typename Compare >
  typename Dictionary< Key, T, Compare >::iterator Dictionary< Key, T, Compare >::end() noexcept
  {
    return data_.end();
  }

  template< typename Key, typename T, typename Compare >
  typename Dictionary< Key, T, Compare >::constIterator Dictionary< Key, T, Compare >::cend() const noexcept
  {
    return data_.cend();
  }

  template< typename Key, typename T, typename Compare >
  typename Dictionary< Key, T, Compare >::constIterator Dictionary< Key, T, Compare >::end() const noexcept
  {
    return cend();
  }

  template< typename Key, typename T, typename Compare >
  typename Dictionary< Key, T, Compare >::constIterator Dictionary< Key, T, Compare >::find(const Key &key) const
  {
    for (auto it = data_.cbegin(); it != data_.cend(); ++it)
    {
      if (!(comp_(it->first, key)) && !(comp_(key, it->first)))
      {
        return it;
      }
    }
    return data_.cend();
  }

  template< typename Key, typename T, typename Compare >
  typename Dictionary< Key, T, Compare >::iterator Dictionary< Key, T, Compare >::find(const Key &key)
  {
    for (auto it = data_.begin(); it != data_.end(); ++it)
    {
      if (!(comp_(it->first, key)) && !(comp_(key, it->first)))
      {
        return it;
      }
    }
    return data_.end();
  }

  template< typename Key, typename T, typename Compare >
  typename Dictionary< Key, T, Compare >::constIterator
    Dictionary< Key, T, Compare >::eraseAfter(constIterator first, constIterator last)
  {
    return data_.eraseAfter(first, last);
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::last() noexcept
  {
    return data_.last();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::constIterator
    Dictionary< Key, Value, Compare >::last() const noexcept
  {
    return clast();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::constIterator
    Dictionary< Key, Value, Compare >::clast() const noexcept
  {
    return data_.clast();
  }

  template< typename Key, typename T, typename Compare >
  T & Dictionary< Key, T, Compare >::at(const Key &key)
  {
    auto it = find(key);
    if (it == data_.end())
    {
      throw std::out_of_range("There is no such key");
    }
    return it->second;
  }

  template< typename Key, typename T, typename Compare >
  const T & Dictionary< Key, T, Compare >::at(const Key &key) const
  {
    auto it = find(key);
    if (it == data_.cend())
    {
      throw std::out_of_range("There is no such key");
    }
    return it->second;
  }

  template< typename Key, typename T, typename Compare >
  bool Dictionary< Key, T, Compare >::isEmpty() const noexcept
  {
    return data_.isEmpty();
  }

  template< typename Key, typename T, typename Compare >
  size_t Dictionary< Key, T, Compare >::size() const noexcept
  {
    return size_;
  }

  template< typename Key, typename T, typename Compare >
  void Dictionary< Key, T, Compare >::clear()
  {
    data_.clear();
    size_ = 0;
  }

  template< typename Key, typename T, typename Compare >
  void Dictionary< Key, T, Compare >::swap(thisT &other)
  {
    std::swap(data_, other.data_);
    std::swap(comp_, other.comp_);
    size_ = other.size_;
    other.size_ = 0;
  }

  template< typename Key, typename T, typename Compare >
  size_t Dictionary< Key, T, Compare >::count(const Key & key) const
  {
    auto it = find(key);
    return (it != end()) ? 1ull : 0ull;
  }

  template< typename Key, typename T, typename Compare >
  bool Dictionary< Key, T, Compare >::contains(const Key &key) const
  {
    return count(key);
  }

  template< typename Key, typename T, typename Compare >
  std::pair
  <
    typename Dictionary< Key, T, Compare >::iterator,
    bool
  > Dictionary< Key, T, Compare >::insert(const valueType &pairToInsert)
  {
    Compare comp = keyComp();
    iterator cur = data_.beforeBegin();
    iterator sup = begin();
    while (sup != end())
    {
      if (!comp(pairToInsert.first, sup->first) && !comp(sup->first, pairToInsert.first))
      {
        return std::make_pair(sup, false);
      }
      else if (comp(pairToInsert.first, sup->first))
      {
        iterator inserted = data_.insertAfter(cur, pairToInsert);
        size_++;
        return std::make_pair(inserted, true);
      }
      cur++;
      sup++;
    }
    iterator inserted = data_.insertAfter(cur, pairToInsert);
    size_++;
    return std::make_pair(inserted, true);
  }

  template< typename Key, typename Value, typename Compare >
  std::pair
  <
    typename Dictionary< Key, Value, Compare >::iterator,
    bool
  > Dictionary< Key, Value, Compare >::insert(const valueType &&val)
  {
    return insert(reinterpret_cast< const valueType && >(val));
  }

  template< typename Key, typename Value, typename Compare >
  template< typename P >
  std::pair
  <
    typename Dictionary< Key, Value, Compare >::iterator,
    bool
  > Dictionary< Key, Value, Compare >::insert(P &&value)
  {
    const valueType temp(std::forward< P >(value));
    return insert(temp);
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iterator
    Dictionary< Key, Value, Compare >::insert(constIterator it, const valueType &value)
  {
    auto existing = find(value.first);
    if (existing != end())
    {
      return existing;
    }
    else
    {
      auto inserted = data_.insert(it, value);
      size_++;
      return iterator(inserted);
    }
  }

  template< typename Key, typename Value, typename Compare >
  template< typename P >
  typename Dictionary< Key, Value, Compare>::iterator
    Dictionary<Key, Value, Compare >::insert(constIterator it, P &&value)
  {
    const valueType tmp(std::forward< P >(value));
    return insert(it, tmp);
  }

  template< typename Key, typename Value, typename Compare >
  template< typename InputIterator >
  void Dictionary< Key, Value, Compare >::insert(InputIterator first, InputIterator last)
  {
    for (auto it = first; it != last; ++it)
    {
      insert(*it);
    }
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::keyCompare
    Dictionary< Key, Value, Compare >::keyComp() const
  {
    return comp_;
  }
}
#endif
