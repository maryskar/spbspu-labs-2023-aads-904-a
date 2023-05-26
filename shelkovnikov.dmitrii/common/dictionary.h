#ifndef SPBSPU_LABS_2023_AADS_904_A_DICTIONARY_H
#define SPBSPU_LABS_2023_AADS_904_A_DICTIONARY_H
#include <utility>
#include <ostream>
#include <functional>
#include "forwardlist.h"
namespace dimkashelk
{
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
      auto res = search(list_.beforeBegin(), k, isEqual);
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
      auto res = search(list_.beforeBegin(), key, isEqual);
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
      auto res = search(list_.beforeBegin(), k, isEqual);
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
        if (isEqual(i.first, x, compare_))
        {
          count++;
        }
      }
      return count;
    }
    iterator_t find(const Key &x)
    {
      auto res = search(list_.beforeBegin(), x, isEqual);
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
      if (isEqual(res->first, x, compare_))
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
        if (isNotEqual(first_it->first, second_it->first))
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
      if (prev != list_.beforeBegin() && isEqual(prev->first, value.first))
      {
        (*prev).second = value.second;
      }
      else
      {
        list_.insertAfter(prev, value);
      }
      return iterator_t(prev);
    }
    std::pair< iterator_t, iterator_t > search(iterator_t start, const Key &key, std::function< bool(const Key &, const Key &) > func)
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
    static bool isEqual(const Key &key1, const Key &key2)
    {
      return !Compare{}(key1, key2) && !Compare{}(key2, key1);
    }
    static bool isNotEqual(const Key &key1, const Key &key2)
    {
      return !isEqual(key1, key2);
    }
  };
  template< class Key, class T, class Compare >
  void swap(Dictionary< Key, T, Compare > &lhs, Dictionary< Key, T, Compare > &rhs )
  {
    lhs.swap(rhs);
  }
  template< typename K, typename V, typename C >
  Dictionary< K, V, C > getIntersection(const Dictionary< K, V, C > &first, const Dictionary< K, V, C > &second)
  {
    Dictionary< K, V, C > result;
    for (auto it_first = second.cbegin(); it_first != second.cend(); it_first++)
    {
      auto res = second.cend();
      for (auto i = first.cbegin(); i != first.cend(); i++)
      {
        if (isEqual(it_first->first, i->first))
        {
          res = i;
          break;
        }
      }
      if (res != second.cend())
      {
        result[res->first] = res->second;
      }
    }
    return result;
  }
  template< typename K, typename V, typename C >
  Dictionary< K, V, C > getComplement(const Dictionary< K, V, C > &first, const Dictionary< K, V, C > &second)
  {
    Dictionary< K, V, C > new_dict;
    if (std::addressof(first) == std::addressof(second))
    {
      return new_dict;
    }
    auto iter_first = first.cbegin();
    auto iter_first_end = first.cend();
    auto iter_second = second.cbegin();
    auto iter_second_end = second.cend();
    C comp = C{};
    while (iter_first != iter_first_end && iter_second != iter_second_end)
    {
      while (iter_second != iter_second_end && comp((*iter_second).first, (*iter_first).first))
      {
        iter_second++;
      }
      if (iter_second == iter_second_end)
      {
        break;
      }
      if (isNotEqual(iter_first->first, iter_second->first))
      {
        new_dict[iter_first->first] = iter_first->second;
      }
      iter_first++;
    }
    while (iter_first != iter_first_end)
    {
      new_dict[iter_first->first] = iter_first->second;
      iter_first++;
    }
    return new_dict;
  }
  template< typename K, typename V, typename C >
  Dictionary< K, V, C > getUnion(const Dictionary< K, V, C > &first, const Dictionary< K, V, C > &second)
  {
    Dictionary< K, V, C > new_dict;
    auto iter_second = second.cbegin();
    auto iter_second_end = second.cend();
    while (iter_second != iter_second_end)
    {
      new_dict[iter_second->first] = iter_second->second;
      iter_second++;
    }
    auto iter_first = first.cbegin();
    auto iter_first_end = first.cend();
    while (iter_first != iter_first_end)
    {
      new_dict[iter_first->first] = iter_first->second;
      iter_first++;
    }
    return new_dict;
  }
  template< typename K, typename V, typename C >
  std::ostream &operator<<(std::ostream &out, Dictionary< K, V, C > &dict)
  {
    if (dict.empty())
    {
      return out << "<EMPTY>";
    }
    auto it = dict.begin();
    auto end = dict.end();
    out << it->first << " " << it->second;
    it++;
    for (; it != end; it++) {
      out << " " << it->first << " " << it->second;
    }
    return out;
  }
}
#endif
