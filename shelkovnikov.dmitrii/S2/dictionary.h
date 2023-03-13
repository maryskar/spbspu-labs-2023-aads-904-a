#ifndef SPBSPU_LABS_2023_AADS_904_A_DICTIONARY_H
#define SPBSPU_LABS_2023_AADS_904_A_DICTIONARY_H
#include <utility>
#include <iterator>
#include <ostream>
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
      list_.free();
      compare_ = other.compare_;
      auto it = list_.begin();
      auto begin = other.list_.begin();
      auto end = other.list_.end();
      while (begin != end)
      {
        list_.insertBefore(it, (*begin));
        begin++;
      }
      return *this;
    }
    void push(Key &k, Value &value)
    {
      auto it = list_.begin();
      auto end = list_.end();
      while (it != end && compare_(k, (*it).first))
      {
        it++;
      }
      if (it == end)
      {
        std::pair< Key, Value > pair(k, value);
        list_.insertBefore(it, pair);
      }
      else if ((*it).first != k)
      {
        std::pair< Key, Value > pair(k, value);
        list_.insertBefore(it, pair);
      }
      else
      {
        (*it).second = value;
      }
    }
    Value &get(const Key &k)
    {
      for (auto i = list_.begin(), end = list_.end(); i != end; i++)
      {
        if ((*i).first == k)
        {
          return (*i).second;
        }
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
