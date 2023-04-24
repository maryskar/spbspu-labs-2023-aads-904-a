#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <stdexcept>
#include "forward_list.h"
namespace tarasenko
{
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
   dict_type& operator=(const dict_type& other)
   {
     if (*this == other)
     {
       return *this;
     }
     list = other.list;
     compare = other.compare;
     return *this;
   }
   dict_type& operator=(dict_type&& other)
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
   friend bool operator<(const dict_type& dict1, const dict_type& dict2)
   {
     auto iter = dict1.list.cbegin();
     auto other_iter = dict2.list.cbegin();
     return iter->first < other_iter->first;
   }
   friend std::ostream& operator<<(std::ostream& output, const dict_type& dict)
   {
     auto iter = dict.list.cbegin();
     output << iter->first << " " << iter->second;
     ++iter;
     while (iter != dict.list.cend())
     {
       output << " " << iter->first << " " << iter->second;
       ++iter;
     }
     return output;
   }
   void push(const Key& k, const Value& v);
   Value get(const Key& k) const;
   void remove(const Key& k);
  private:
   ForwardList< std::pair< Key, Value > > list;
   Compare compare;
  };

  template< typename Key, typename Value, typename Compare >
  void Dictionary< Key, Value, Compare >::push(const Key& k, const Value& v)
  {
    std::pair< Key, Value > data(k, v);
    auto current = list.begin();
    while (current != list.end() && compare(*current, data))
    {
      ++current;
    }
    list.addBefore(current.getNode(), data);
  };

  template< typename Key, typename Value, typename Compare >
  Value Dictionary< Key, Value, Compare >::get(const Key& k) const
  {
    auto current = list.cbegin();
    while (current != list.cend() && (k != current->first))
    {
      ++current;
    }
    if (current != list.cend() && (k == current->first))
    {
      return current->second;
    }
    else
    {
      throw std::invalid_argument("Key not found");
    }
  };
  template< typename Key, typename Value, typename Compare >
  void Dictionary< Key, Value, Compare >::remove(const Key& k)
  {
    std::pair< Key, Value > data(k);
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
