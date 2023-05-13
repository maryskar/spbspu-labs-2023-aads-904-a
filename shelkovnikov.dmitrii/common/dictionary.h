#ifndef SPBSPU_LABS_2023_AADS_904_A_DICTIONARY_H
#define SPBSPU_LABS_2023_AADS_904_A_DICTIONARY_H
#include <utility>
#include <ostream>
#include <algorithm>
#include "forwardlist.h"
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
      compare_(Compare())
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
      compare_(Compare())
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
      for (auto i = begin(); i != end(); i++)
      {
        if ((*i).first == k)
        {
          return (*i).second;
        }
      }
      throw std::out_of_range("Out of range");
    }
    const Value &at(const Key &k) const
    {
      return at(k);
    }
    Value &operator[](Key &&key)
    {
      auto prev = list_.beforeBegin();
      auto cur = begin();
      for (; cur != end(); prev = cur, cur++)
      {
        if ((*cur).first == key)
        {
          return (*cur).second;
        }
        if (compare_((*cur).first, key))
        {
          break;
        }
      }
      value_type value_to_insert = {key, Value()};
      auto res = list_.insertAfter(prev, value_to_insert);
      return (*res).second;
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
      auto prev = list_.beforeBegin();
      for (auto cur = begin(); cur != end(); prev = cur, cur++)
      {
        if ((*cur).first == k)
        {
          list_.eraseAfter(prev);
          return 1;
        }
      }
      return 0;
    }
    void swap(Dictionary< Key, Value, Compare > &other)
    {
      list_.swap(other.list_);
    }
    template< class K >
    size_t count(const K &x) const
    {
      size_t count = 0;
      for (auto i: *this)
      {
        if (i.first == x)
        {
          count++;
        }
      }
      return count;
    }
    template< class K >
    iterator_t find(const K &x)
    {
      for (auto i = begin(); i != end(); i++)
      {
        if ((*i).first == x)
        {
          return i;
        }
      }
      return end();
    }
    template< class K >
    std::pair< iterator_t, iterator_t > equal_range(const K& x)
    {
      return {lower_bound(x), upper_bound(x)};
    }
    template< class K >
    std::pair< const_iterator_t, const_iterator_t > equal_range(const K& x) const
    {
      return {lower_bound(x), upper_bound(x)};
    }
    template< class K >
    iterator_t lower_bound(const K &x)
    {
      auto prev = begin();
      auto cur = begin();
      for (auto i = begin(); i != end(); i++)
      {
        if ((*i).first >= x)
        {
          return i;
        }
      }
      return end();
    }
    template< class K >
    const_iterator_t lower_bound(const K &x) const
    {
      return lower_bound(x);
    }
    template< class K >
    iterator_t upper_bound(const K &x)
    {
      auto res = lower_bound(x);
      if ((*res).first == x)
      {
        res++;
      }
      return res;
    }
    template < class K >
    const_iterator_t upper_bound(const K &x) const
    {
      return upper_bound(x);
    }
    friend std::ostream &operator<<(std::ostream &out, dict_type &dict)
    {
      if (dict.empty())
      {
        return out << "<EMPTY>";
      }
      auto it = dict.list_.begin();
      auto end = dict.list_.end();
      out << (*it).first << " " << (*it).second;
      it++;
      for (; it != end; it++) {
        out << " " << (*it).first << " " << (*it).second;
      }
      return out;
    }
    friend bool operator==(const dict_type &first, const dict_type &second)
    {
      auto first_it = first.cbegin();
      auto second_it = second.cbegin();
      for (; first_it != first.cend() && second_it != second.cend(); first_it++, second_it++)
      {
        if ((*first_it) != (*second_it))
        {
          return false;
        }
      }
      return true;
    }
    friend bool operator!=(const dict_type &first, const dict_type &second)
    {
      return !(first == second);
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
      if (prev != list_.beforeBegin() && (*prev).first == value.first)
      {
        (*prev).second = value.second;
      }
      else
      {
        list_.insertAfter(prev, value);
      }
      return iterator_t(prev);
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
    for (auto it_first = second.list_.cbegin(); it_first != second.list_.cend(); it_first++)
    {
      ForwardListIterator< std::pair< K, V > > res = second.list_.cend();
      for (auto i = first.list_.cbegin(); i != first.list_.cend(); i++)
      {
        if ((*it_first).first == (*i).first)
        {
          res = i;
          break;
        }
      }
      if (res != second.list_.cend())
      {
        result.push(*res);
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
    auto iter_first = first.list_.cbegin();
    auto iter_first_end = first.list_.cend();
    auto iter_second = second.list_.cbegin();
    auto iter_second_end = second.list_.cend();
    while (iter_first != iter_first_end && iter_second != iter_second_end)
    {
      while (iter_second != iter_second_end && C{}((*iter_second).first, (*iter_first).first))
      {
        iter_second++;
      }
      if (iter_second == iter_second_end)
      {
        break;
      }
      if (details::isNotEqual< K, C >(iter_first->first, iter_second->first))
      {
        new_dict.push(value_type(*iter_first));
      }
      iter_first++;
    }
    while (iter_first != iter_first_end)
    {
      new_dict.push(*iter_first);
      iter_first++;
    }
    return new_dict;
  }
  template< typename K, typename V, typename C >
  Dictionary< K, V, C > getUnion(const Dictionary< K, V, C > &first, const Dictionary< K, V, C > &second)
  {
    Dictionary< K, V, C > new_dict;
    auto iter_second = second.list_.cbegin();
    auto iter_second_end = second.list_.cend();
    while (iter_second != iter_second_end)
    {
      new_dict.push(value_type(*iter_second));
      iter_second++;
    }
    auto iter_first = first.list_.cbegin();
    auto iter_first_end = first.list_.cend();
    while (iter_first != iter_first_end)
    {
      new_dict.push(value_type(*iter_first));
      iter_first++;
    }
    return new_dict;
  }
}
#endif
