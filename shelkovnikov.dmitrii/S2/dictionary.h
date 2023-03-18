#ifndef SPBSPU_LABS_2023_AADS_904_A_DICTIONARY_H
#define SPBSPU_LABS_2023_AADS_904_A_DICTIONARY_H
#include <utility>
#include <iterator>
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
    Dictionary():
      list_(),
      compare_(Compare{})
    {}
    Dictionary(const dict_type &dict):
      list_(dict.list_),
      compare_(dict.compare_)
    {}
    ~Dictionary() = default;
    dict_type &operator=(const dict_type &other)
    {
      if (this == std::addressof(other))
      {
        return *this;
      }
      list_.free();
      compare_ = other.compare_;
      if (other.list_.begin() == other.list_.end())
      {
        return *this;
      }
      auto begin = other.list_.begin();
      auto end = other.list_.end();
      list_.pushFront(*begin);
      begin++;
      while (begin != end)
      {
        list_.pushBack(*begin);
        begin++;
      }
      return *this;
    }
    void push(const Key &k, const Value &value)
    {
      auto comp = [&](const auto &item)
      {
        return compare_(item.first, k);
      };
      auto it = std::find_if(list_.begin(), list_.end(), comp);
      if (it == list_.begin())
      {
        list_.pushFront(std::pair< Key, Value >(k, value));
      }
      else if (it != list_.end())
      {
        it--;
        list_.insertAfter(it, std::pair< Key, Value >(k, value));
      }
      else
      {
        list_.pushBack(std::pair< Key, Value >(k, value));
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
    friend std::ostream &operator<<(std::ostream &out, dict_type dict)
    {
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
      return getResult(first, second, "-");
    }
    friend dict_type operator&(const dict_type &first, const dict_type &second)
    {
      return getResult(first, second, "&");
    }
    friend dict_type operator|(const dict_type &first, const dict_type &second)
    {
      dict_type new_dict;
      auto iter_second = second.list_.begin();
      auto iter_second_end = second.list_.end();
      while (iter_second != iter_second_end)
      {
        Key key = (*iter_second).first;
        Value value = (*iter_second).second;
        new_dict.push(key, value);
        iter_second++;
      }
      auto iter_first = first.list_.begin();
      auto iter_first_end = first.list_.end();
      while (iter_first != iter_first_end)
      {
        Key key = (*iter_first).first;
        Value value = (*iter_first).second;
        new_dict.push(key, value);
        iter_first++;
      }
      return new_dict;
    }
    friend bool operator>(const dict_type &first, const dict_type &second)
    {
      return first.list_ > second.list_;
    }
  private:
    ForwardList< std::pair< Key, Value > > list_;
    Compare compare_;
    static dict_type getResult(const dict_type &first, const dict_type &second, const std::string& operation)
    {
      dict_type new_dict;
      auto iter_first = first.list_.begin();
      auto iter_first_end = first.list_.end();
      auto iter_second = second.list_.begin();
      auto iter_second_end = second.list_.end();
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
        bool operand_and = operation == "&" && (*iter_first).first == (*iter_second).first;
        bool operand_minus = operation == "-" && (*iter_first).first != (*iter_second).first;
        if (operand_and || operand_minus)
        {
          Key key = (*iter_first).first;
          Value value = (*iter_first).second;
          new_dict.push(key, value);
        }
        iter_first++;
      }
      while (operation == "-" && iter_first != iter_first_end)
      {
        Key key = (*iter_first).first;
        Value value = (*iter_first).second;
        new_dict.push(key, value);
        iter_first++;
      }
      return new_dict;
    }
  };
}
#endif
