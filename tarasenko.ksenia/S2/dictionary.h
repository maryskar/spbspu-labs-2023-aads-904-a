#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <stdexcept>
#include "forward_list.h"
namespace tarasenko
{
  template< typename Key, typename Value >
  struct Pair
  {
    Key key_;
    Value value_;

    Pair()
    {};

    Pair(const Key& key):
      key_(key)
    {};

    Pair(const Key& key, const Value& val):
      key_(key),
      value_(val)
    {};

    Pair(const Pair& p):
      key_(p.key_),
      value_(p.value_)
    {}

    Pair< Key, Value >& operator=(const Pair& p)
    {
      key_ = p.key_;
      value_ = p.value_;
      return *this;
    }

    bool operator<(const Pair< Key, Value >& p) const
    {
      return key_ < p.key_;
    }

    bool operator==(const Pair< Key, Value >& p) const
    {
      return key_ == p.key_;
    }
  };

  template< typename Key, typename Value/*, typename Compare*/ >
  class Dictionary
  {
  public:
   Dictionary()
   {}
   ~Dictionary()
   {
     list.clear();
   }
   void push(const Key& k, const Value& v);
   Value get(const Key& k);
   void remove(const Key& k);
  private:
   ForwardList< Pair< Key, Value > > list;
  };

  template< typename Key, typename Value/*, typename Compare*/ >
  void Dictionary< Key, Value/*, Compare*/ >::push(const Key& k, const Value& v)
  {
    Pair< Key, Value > data(k, v);
    list.insert(data);
  };

  template< typename Key, typename Value/*, typename Compare*/ >
  Value Dictionary< Key, Value/*, Compare*/ >::get(const Key& k)
  {
    ForwardListIterator< Pair< Key, Value >> null_iter;
    ForwardListIterator< Pair< Key, Value >> iter = list.begin();
    while (iter != null_iter && (k != iter->key_))
    {
      ++iter;
    }
    if (iter != null_iter && (k == iter->key_))
    {
      return iter->value_;
    }
    else
    {
      throw std::invalid_argument("Key not found");
    }
  };
  template< typename Key, typename Value/*, typename Compare*/ >
  void Dictionary< Key, Value/*, Compare*/ >::remove(const Key& k)
  {
    Pair< Key, Value > data(k);
    list.removeData(data);
  };
}

#endif
