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
      compare_(std::less< Key >())
    {}
    void push(Key k, Value value)
    {
      if (list_.empty())
      {
        list_.pushFront(std::pair< Key, Value >(k, value));
        return;
      }
      if (compare_((*list_.begin()).first, k))
      {
        list_.pushFront(std::pair< Key, Value >(k, value));
        return;
      }
      auto it = list_.begin();
      auto end = list_.end();
      while (it != end && compare_(k, (*it).first))
      {
        it++;
      }
      if (it == end)
      {
        list_.pushBack(std::pair< Key, Value >(k, value));
      }
      else
      {
        it--;
        list_.insertAfter(it, std::pair< Key, Value >(k, value));
      }
    }
    Value get(Key k)
    {

    }
    Value drop(Key k)
    {

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
