#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <stdexcept>
#include <forward_list.h>

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
     list = other.list;
     compare = other.compare;
     return *this;
   }
   dict_type& operator=(dict_type&& other)
   {
     list = std::move(other.list);
     compare = other.compare;
     return *this;
   }
   ~Dictionary() = default;

   friend bool operator<(const dict_type& dict1, const dict_type& dict2)
   {
     auto iter = dict1.list.cbegin();
     auto other_iter = dict2.list.cbegin();
     return iter->first < other_iter->first;
   }

   friend std::ostream& operator<<(std::ostream& output, const dict_type& dict)
   {
     if (!dict.isEmpty())
     {
       auto iter = dict.list.cbegin();
       output << iter->first << " " << iter->second;
       ++iter;
       while (iter != dict.list.cend())
       {
         output << " " << iter->first << " " << iter->second;
         ++iter;
       }
     }
     return output;
   }

   friend dict_type operator-(const dict_type& left, const dict_type& right)
   {
     dict_type result = left;
     if (!left.isEmpty() && !right.isEmpty())
     {
       auto iter_left = left.list.cbegin();
       for (; iter_left != left.list.cend(); iter_left++)
       {
         if (right.find((*iter_left).first))
         {
           result.remove((*iter_left).first);
         }
       }
     }
     return result;
   }

   friend dict_type operator&&(const dict_type& left, const dict_type& right)
   {
     if (right.isEmpty())
     {
       return right;
     }
     dict_type result;
     if (!left.isEmpty())
     {
       auto iter_left = left.list.cbegin();
       for (; iter_left != left.list.cend(); iter_left++)
       {
         if (right.find((*iter_left).first))
         {
           result.push((*iter_left).first, (*iter_left).second);
         }
       }
     }
     return result;
   }

   friend dict_type operator||(const dict_type& left, const dict_type& right)
   {
     if (left.isEmpty())
     {
       return right;
     }
     dict_type result = left;
     if (!right.isEmpty())
     {
       auto iter_right = right.list.cbegin();
       for (; iter_right != right.list.cend(); iter_right++)
       {
         if (!left.find((*iter_right).first))
         {
           result.push((*iter_right).first, (*iter_right).second);
         }
       }
     }
     return result;
   }

   void push(const Key& k, const Value& v);
   Value get(const Key& k) const;
   bool find(const Key& k) const;
   void remove(const Key& key);
   bool isEmpty() const;

  private:
   ForwardList< std::pair< Key, Value > > list;
   Compare compare;
  };

  template< typename Key, typename Value, typename Compare >
  void Dictionary< Key, Value, Compare >::push(const Key& k, const Value& v)
  {
    std::pair< Key, Value > data(k, v);
    if (find(k))
    {
      remove(k);
    }
    auto current = list.cbegin();
    while (current != list.cend() && compare(*current, data))
    {
      ++current;
    }
    list.insertBefore(current, data);
  };

  template< typename Key, typename Value, typename Compare >
  Value Dictionary< Key, Value, Compare >::get(const Key& k) const
  {
    if (!isEmpty())
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
    }
    throw std::invalid_argument("Key not found");
  }

  template< typename Key, typename Value, typename Compare >
  bool Dictionary< Key, Value, Compare >::find(const Key& k) const
  {
    if (!isEmpty())
    {
      auto current = list.cbegin();
      while (current != list.cend() && (k != current->first))
      {
        ++current;
      }
      if (current != list.cend() && (k == current->first))
      {
        return true;
      }
    }
    return false;
  }

  template< typename Key, typename Value, typename Compare >
  void Dictionary< Key, Value, Compare >::remove(const Key& key)
  {
    auto prev = list.cbeforeBegin();
    auto current = list.cbegin();
    while (current != list.end())
    {
      if (current->first == key)
      {
        ++current;
        list.eraseAfter(prev);
        ++prev;
        continue;
      }
      ++current;
      ++prev;
    }
  }

  template< typename Key, typename Value, typename Compare >
  bool Dictionary< Key, Value, Compare >::isEmpty() const
  {
    return list.isEmpty();
  }
}
#endif
