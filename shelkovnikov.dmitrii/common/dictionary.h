#ifndef SPBSPU_LABS_2023_AADS_904_A_DICTIONARY_H
#define SPBSPU_LABS_2023_AADS_904_A_DICTIONARY_H
#include <utility>
#include <ostream>
#include <algorithm>
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
      compare_(Compare{})
    {}
    Dictionary(const dict_type &dict):
      list_(dict.list_),
      compare_(dict.compare_)
    {}
    Dictionary(dict_type &&dict):
      list_(std::move(dict.list_)),
      compare_(dict.compare_)
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
    //iterator_t eraseAfter(const_iterator_t pos);
    //iterator_t eraseAfter(const_iterator_t first, const_iterator_t second);
    //iterator_t erase(const Key &k);
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
    Value &get(const Key &k)
    {
      auto comp = [&](const auto &item)
      {
        return item.first == k;
      };
      auto it = std::find_if(list_.begin(), list_.end(), comp);
      if (it != list_.end())
      {
        return (*it).second;
      }
      throw std::runtime_error("Nothing to return");
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
    friend dict_type operator-(const dict_type &first, const dict_type &second)
    {
      if (std::addressof(first) == std::addressof(second))
      {
        return dict_type();
      }
      dict_type new_dict;
      auto iter_first = first.list_.cbegin();
      auto iter_first_end = first.list_.cend();
      auto iter_second = second.list_.cbegin();
      auto iter_second_end = second.list_.cend();
      while (iter_first != iter_first_end && iter_second != iter_second_end)
      {
        while (iter_second != iter_second_end && Compare{}((*iter_first).first, (*iter_second).first))
        {
          iter_second++;
        }
        if (iter_second == iter_second_end)
        {
          break;
        }
        if ((*iter_first).first != (*iter_second).first)
        {
          Key key = (*iter_first).first;
          Value value = (*iter_first).second;
          new_dict.push(value_type(key, value));
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
    friend dict_type operator&(const dict_type &first, const dict_type &second)
    {
      dict_type result;
      for (auto it_first = second.list_.cbegin(); it_first != second.list_.cend(); it_first++)
      {
        auto comp = [&](const auto &item)
        {
          return item.first == (*it_first).first;
        };
        auto res = std::find_if(first.list_.cbegin(), first.list_.cend(), comp);
        if (res != second.list_.cend())
        {
          result.push(*res);
        }
      }
      return result;
    }
    friend dict_type operator|(const dict_type &first, const dict_type &second)
    {
      dict_type new_dict;
      auto iter_second = second.list_.cbegin();
      auto iter_second_end = second.list_.cend();
      while (iter_second != iter_second_end)
      {
        Key key = (*iter_second).first;
        Value value = (*iter_second).second;
        new_dict.push(value_type(key, value));
        iter_second++;
      }
      auto iter_first = first.list_.cbegin();
      auto iter_first_end = first.list_.cend();
      while (iter_first != iter_first_end)
      {
        Key key = (*iter_first).first;
        Value value = (*iter_first).second;
        new_dict.push(value_type(key, value));
        iter_first++;
      }
      return new_dict;
    }
  private:
    ForwardList< value_type > list_;
    Compare compare_;
    iterator_t push(value_type value)
    {
      auto it = list_.begin();
      auto prev = list_.beforeBegin();
      for (; it != list_.end(); it++)
      {
        if (compare_((*it).first, value.first))
        {
          break;
        }
        prev = it;
      }
      if (it == list_.end())
      {
        if (prev != list_.beforeBegin() && (*prev).first == value.first)
        {
          (*prev).second = value.second;
        }
        else
        {
          list_.insertAfter(prev, value_type(value.first, value.second));
        }
      }
      else if ((*prev).first == value.first)
      {
        (*prev).second = value.second;
      }
      else if (it == list_.begin())
      {
        list_.pushFront(value_type(value.first, value.second));
        return begin();
      }
      else
      {
        list_.insertAfter(prev, value_type(value.first, value.second));
        return iterator_t(it);
      }
      return iterator_t(prev);
    }
  };
}
#endif
