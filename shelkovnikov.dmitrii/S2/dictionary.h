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
    Dictionary():
      list_(),
      compare_(Compare{})
    {}
    ~Dictionary() = default;
    Dictionary< Key, Value, Compare > &operator=(const Dictionary< Key, Value, Compare > &other)
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
    void push(Key k, Value value)
    {
      auto it = list_.begin();
      auto end = list_.end();
      while (it != end && compare_(k, (*it).first))
      {
        it++;
      }
      std::pair< Key, Value > pair(k, value);
      list_.insertBefore(it, pair);
    }
    Value get(Key k)
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
    Value drop(Key k)
    {
      for (auto i = list_.begin(), end = list_.end(); i != end; i++)
      {
        if ((*i).first == k)
        {
          std::pair< Key, Value > *data = list_.remove(i);
          Value value = data->second;
          delete data;
          return value;
        }
      }
      throw std::runtime_error("Nothing to return");
    }
    bool empty()
    {
      return list_.empty();
    }
    friend std::ostream &operator<<(std::ostream &out, Dictionary< Key, Value, Compare > dict)
    {
      for (auto it = dict.list_.begin(), end = dict.list_.end(); it != end; it++) {
        out << (*it).first << " " << (*it).second << " ";
      }
      return out;
    }
    friend Dictionary< Key, Value, Compare > operator-(Dictionary< Key, Value, Compare > &first, Dictionary< Key, Value, Compare > &second)
    {
      Dictionary< Key, Value, Compare > new_dict;
      for (auto &&iter_first: first.list_)
      {
        bool contains = false;
        for (auto &&iter_second: second.list_)
        {
          if (iter_first.first == iter_second.first)
          {
            contains = true;
            break;
          }
        }
        if (!contains)
        {
          new_dict.push(iter_first.first, iter_first.second);
        }
      }
      return new_dict;
    }
  private:
    ForwardList< std::pair< Key, Value > > list_;
    Compare compare_;
  };
}
#endif
