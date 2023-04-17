#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <stdexcept>
#include "forward_list.h"
namespace tarasenko
{
  namespace details
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
  }

  template< typename Key, typename Value, typename Compare >
  class Dictionary
  {
  public:
   using dict_type = Dictionary< Key, Value, Compare >;
   Dictionary():
     list(),
     compare(Compare{})
   {}
   Dictionary(const Dictionary< Key, Value, Compare >& other):
     list(other.list),
     compare(other.compare)
   {}
   Dictionary(Dictionary< Key, Value, Compare >&& other):
     list(std::move(other.list)),
     compare(other.compare)
   {}
   dict_type& operator==(const dict_type& other)
   {
     if (*this == other)
     {
       return *this;
     }
     list = other.list;
     compare = other.compare;
     return *this;
   }
   dict_type& operator==(dict_type&& other)
   {
     if (*this == other)
     {
       return *this;
     }
     list = std::move(other.list);
     compare = other.compare;
     return *this;
   }
   ~Dictionary()
   {
     list.clear();
   }
   void push(const Key& k, const Value& v);
   Value get(const Key& k);
   void remove(const Key& k);
  private:
   ForwardList< details::Pair< Key, Value > > list;
   Compare compare;
  };

  template< typename Key, typename Value, typename Compare >
  void Dictionary< Key, Value, Compare >::push(const Key& k, const Value& v)
  {
    details::Pair< Key, Value > data(k, v);
    auto current = list.begin();
    while (current != list.end() && compare(*current, data))
    {
      ++current;
    }
    list.addBefore(current.getNode(), data);
  };

  template< typename Key, typename Value, typename Compare >
  Value Dictionary< Key, Value, Compare >::get(const Key& k)
  {
    auto current = list.begin();
    while (current != list.end() && (k != current->key_))
    {
      ++current;
    }
    if (current != list.end() && (k == current->key_))
    {
      return current->value_;
    }
    else
    {
      throw std::invalid_argument("Key not found");
    }
  };
  template< typename Key, typename Value, typename Compare >
  void Dictionary< Key, Value, Compare >::remove(const Key& k)
  {
    details::Pair< Key, Value > data(k);
    auto current = list.begin();
    while (current != list.end())
    {
      if (*current == data)
      {
        auto to_delete = current;
        ++current;
        list.removeNode(to_delete.getNode());
        continue;
      }
      ++current;
    }
  };
}

#endif
