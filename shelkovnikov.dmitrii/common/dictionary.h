#ifndef SPBSPU_LABS_2023_AADS_904_A_DICTIONARY_H
#define SPBSPU_LABS_2023_AADS_904_A_DICTIONARY_H
#include <utility>
#include <ostream>
#include <functional>
#include "forwardlist/forwardlist.h"
namespace dimkashelk
{
  namespace details
  {
    template< typename K, typename Comp >
    bool isEqual(K key1, K key2)
    {
      return !Comp{}(key1, key2) && !Comp{}(key2, key1);
    }
    template< typename K, typename Comp >
    bool isNotEqual(K key1, K key2)
    {
      return !isEqual< K, Comp >(key1, key2);
    }
  }
  template< typename Key, typename Value, typename Compare >
  class Dictionary
  {
  public:
    using dict_type = Dictionary< Key, Value, Compare >;
    using value_type = std::pair< Key, Value >;
    using iterator_t = dimkashelk::ForwardListIterator< value_type >;
    using const_iterator_t = dimkashelk::ForwardListIteratorConst< value_type >;
    Dictionary():
      list_(),
      compare_()
    {}
    Dictionary(const dict_type &dict):
      list_(dict.list_),
      compare_(dict.compare_)
    {}
    Dictionary(dict_type &&dict):
      list_(std::move(dict.list_)),
      compare_(dict.compare_)
    {}
    Dictionary(std::initializer_list< value_type > init):
      list_(init),
      compare_()
    {}
    ~Dictionary() = default;
    dict_type &operator=(const dict_type &other)
    {
      if (this == std::addressof(other))
      {
        return *this;
      }
      list_ = other.list_;
      return *this;
    }
    dict_type &operator=(dict_type &&other)
    {
      if (this == std::addressof(other))
      {
        return *this;
      }
      list_ = std::move(other.list_);
      return *this;
    }
    Value &at(const Key &k)
    {
      auto res = search(list_.beforeBegin(), k, details::isEqual< Key, Compare >);
      if (res.second == end())
      {
        throw std::out_of_range("Out of range");
      }
      return res.second->second;
    }
    const Value &at(const Key &k) const
    {
      return at(k);
    }
    Value &operator[](const Key &key)
    {
      auto res = search(list_.beforeBegin(), key, details::isEqual< Key, Compare >);
      if (res.second == end())
      {
        value_type value_to_insert = {key, Value()};
        auto insert_res = list_.insertAfter(res.first, value_to_insert);
        return insert_res->second;
      }
      return res.second->second;
    }
    Value &operator[](Key &&key)
    {
      return this->operator[](key);
    }
    iterator_t begin()
    {
      return list_.begin();
    }
    const_iterator_t cbegin() const
    {
      return list_.cbegin();
    }
    iterator_t end()
    {
      return list_.end();
    }
    const_iterator_t cend() const
    {
      return list_.cend();
    }
    bool empty() const noexcept
    {
      return list_.empty();
    }
    size_t size() const noexcept
    {
      return list_.size_;
    }
    void clear() noexcept
    {
      list_.clear();
    }
    template< class ... Args >
    std::pair< iterator_t, bool > emplace(Args&&... args)
    {
      try
      {
        auto iter = push(std::forward< value_type >(value_type(args...)));
        return {iter, true};
      }
      catch (...)
      {
        return {begin(), false};
      }
    }
    iterator_t eraseAfter(const_iterator_t pos)
    {
      return list_.eraseAfter(pos);
    }
    iterator_t eraseAfter(const_iterator_t first, const_iterator_t second)
    {
      return list_.eraseAfter(first, second);
    }
    size_t erase(const Key &k)
    {
      auto res = search(list_.beforeBegin(), k, details::isEqual< Key, Compare >);
      if (res.second == end())
      {
        return 0;
      }
      list_.eraseAfter(res.first);
      return 1;
    }
    void swap(Dictionary< Key, Value, Compare > &other)
    {
      list_.swap(other.list_);
    }
    size_t count(const Key &x) const
    {
      size_t count = 0;
      for (auto i: *this)
      {
        if (details::isEqual(i.first, x, compare_))
        {
          count++;
        }
      }
      return count;
    }
    iterator_t find(const Key &x)
    {
      auto res = search(list_.beforeBegin(), x, details::isEqual< Key, Compare >);
      return res.second;
    }
    std::pair< iterator_t, iterator_t > equal_range(const Key &x)
    {
      return {lower_bound(x), upper_bound(x)};
    }
    std::pair< const_iterator_t, const_iterator_t > equal_range(const Key &x) const
    {
      return {lower_bound(x), upper_bound(x)};
    }
    iterator_t lower_bound(const Key &x)
    {
      auto res = search(list_.beforeBegin(), x, !compare_);
      return res.second;
    }
    const_iterator_t lower_bound(const Key &x) const
    {
      return lower_bound(x);
    }
    iterator_t upper_bound(const Key &x)
    {
      auto res = lower_bound(x);
      if (details::isEqual(res->first, x, compare_))
      {
        res++;
      }
      return res;
    }
    const_iterator_t upper_bound(const Key &x) const
    {
      return upper_bound(x);
    }
    bool operator==(const dict_type &second)
    {
      auto first_it = cbegin();
      auto second_it = second.cbegin();
      for (; first_it != cend() && second_it != second.cend(); first_it++, second_it++)
      {
        if (details::isNotEqual(first_it->first, second_it->first))
        {
          return false;
        }
      }
      return true;
    }
    bool operator!=(const dict_type &second)
    {
      return !(*this == second);
    }
  private:
    ForwardList< value_type > list_;
    Compare compare_;
    iterator_t push(const value_type &value)
    {
      auto it = list_.begin();
      auto prev = list_.beforeBegin();
      for (; it != list_.end(); it++)
      {
        if (compare_(value.first, (*it).first))
        {
          break;
        }
        prev = it;
      }
      if (prev != list_.beforeBegin() && details::isEqual< Key, Compare >(prev->first, value.first))
      {
        (*prev).second = value.second;
      }
      else
      {
        list_.insertAfter(prev, value);
      }
      return iterator_t(prev);
    }
    std::pair< iterator_t, iterator_t > search(iterator_t start, const Key &key, std::function< bool(Key, Key) > func)
    {
      auto prev = start;
      start++;
      auto cur = start;
      for (; cur != end(); prev = cur, cur++)
      {
        if (func(cur->first, key))
        {
          return {prev, cur};
        }
      }
      return {prev, cur};
    }
  };
  template< class Key, class T, class Compare >
  void swap(Dictionary< Key, T, Compare > &lhs, Dictionary< Key, T, Compare > &rhs )
  {
    lhs.swap(rhs);
  }
}
#endif
