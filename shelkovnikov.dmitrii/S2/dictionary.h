#ifndef SPBSPU_LABS_2023_AADS_904_A_DICTIONARY_H
#define SPBSPU_LABS_2023_AADS_904_A_DICTIONARY_H
#include <utility>
#include <iterator>
#include <ostream>
#include "forwardlist.h"
namespace dimkashelk
{
  template< class Key, class Value, class Compare >
  class Dictionary
  {
  public:
    explicit Dictionary(Compare compare):
      list_(),
      compare_(compare)
    {}
    ~Dictionary() = default;
    void push(Key k, Value value)
    {
      auto it = list_.begin();
      auto end = list_.end();
      while (it != end && compare_(k, (*it).first))
      {
        it++;
      }
      list_.insertBefore(it, std::pair<Key, Value>(k, value));
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
          std::pair< Key, Value > data = *i;
          list_.remove(i);
          return data.second;
        }
      }
      throw std::runtime_error("Nothing to return");
    }
    friend std::ostream &operator<<(std::ostream &out, Dictionary< Key, Value, Compare > dict)
    {
      for (auto it = dict.list_.begin(), end = dict.list_.end(); it != end; it++) {
        out << (*it).first << " " << (*it).second << "\n";
      }
      return out;
    }
  private:
    ForwardList< std::pair< Key, Value > > list_;
    Compare compare_;
  };
}
#endif
