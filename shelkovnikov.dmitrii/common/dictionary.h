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
    void push(const Key &k, const Value &value)
    {
      auto it = list_.begin();
      auto prev = list_.beforeBegin();
      for (; it != list_.end(); it++)
      {
        if (compare_((*it).first, k))
        {
          break;
        }
        prev = it;
      }
      if (it == list_.end())
      {
        list_.insertAfter(prev, value_type(k, value));
      }
      else if ((*it).first == k)
      {
        (*it).second = value;
      }
      else if (it == list_.begin())
      {
        list_.pushFront(value_type(k, value));
      }
      else
      {
        list_.insertAfter(prev, value_type(k, value));
      }
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
    bool empty()
    {
      return list_.empty();
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
          new_dict.push(key, value);
        }
        iter_first++;
      }
      while (iter_first != iter_first_end)
      {
        new_dict.push((*iter_first).first, (*iter_first).second);
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
          result.push((*res).first, (*res).second);
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
        new_dict.push(key, value);
        iter_second++;
      }
      auto iter_first = first.list_.cbegin();
      auto iter_first_end = first.list_.cend();
      while (iter_first != iter_first_end)
      {
        Key key = (*iter_first).first;
        Value value = (*iter_first).second;
        new_dict.push(key, value);
        iter_first++;
      }
      return new_dict;
    }
  private:
    ForwardList< value_type > list_;
    Compare compare_;
  };
}
#endif
