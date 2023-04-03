#ifndef SPBSPU_LABS_2023_AADS_904_A_DICTIONARY_H
#define SPBSPU_LABS_2023_AADS_904_A_DICTIONARY_H
#include <utility>
#include <iterator>
#include <ostream>
#include <algorithm>
#include "twoThreeTree.h"
namespace dimkashelk
{
  template< typename Key, typename Value, typename Compare >
  class Dictionary
  {
  public:
    using dict_type = Dictionary< Key, Value, Compare >;
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
    ~Dictionary() = default;
    void push(const Key &k, const Value &v)
    {
      list_.insert(k, v);
    }
    Value &get(const Key &k)
    {
      return list_.get(k);
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
      out << *it << " " << it.value;
      it++;
      for (; it != end; it++) {
        out << " " << *it << " " << it.value;
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
      for (auto iter = first.list_.begin(); iter != first.list_.end(); iter++)
      {
        if (!second.list_.contains(*iter))
        {
          new_dict.push(*iter, iter.value);
        }
      }
      return new_dict;
    }
    friend dict_type operator&(const dict_type &first, const dict_type &second)
    {
      dict_type result;
      for (auto it_first = first.list_.begin(); it_first != first.list_.end(); it_first++)
      {
        if (second.list_.contains(*it_first))
        {
          result.push(*it_first, it_first.value);
        }
      }
      return result;
    }
    friend dict_type operator|(const dict_type &first, const dict_type &second)
    {
      dict_type new_dict;
      for (auto it_second = second.list_.begin(); it_second != second.list_.end(); it_second++)
      {
        new_dict.push(*it_second, it_second.value);
      }
      for (auto it_first = first.list_.begin(); it_first != first.list_.end(); it_first++)
      {
        new_dict.push(*it_first, it_first.value);
      }
      return new_dict;
    }
    friend bool operator>(const dict_type &first, const dict_type &second)
    {
      return first.list_ > second.list_;
    }
    friend bool operator<(const dict_type &first, const dict_type &second)
    {
      return first.list_ < second.list_;
    }
  private:
    TwoThreeTree< Key, Value, Compare > list_;
    Compare compare_;
  };
}
#endif
