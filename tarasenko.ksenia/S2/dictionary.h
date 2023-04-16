#ifndef DICTIONARY_H
#define DICTIONARY_H
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

  template< typename Key, typename Value, typename Compare >
  class Dictionary
  {
  public:
   void push(Key& k, Value& v);
   Value get(Key& k);
   Value drop(Key& k); // !!!
   //...
   //Value find(Key& k);
   //void remove(Key& k);
  private:
   ForwardList< Pair< Key, Value > > list;
  };

  template< typename Key, typename Value, typename Compare >
  void Dictionary< Key, Value, Compare >::push(Key& k, Value& v)
  {

  };

  template< typename Key, typename Value, typename Compare >
  Value Dictionary< Key, Value, Compare >::get(Key& k)
  {

  };

  template< typename Key, typename Value, typename Compare >
  Value Dictionary< Key, Value, Compare >::drop(Key& k)
  {

  };
}

#endif
