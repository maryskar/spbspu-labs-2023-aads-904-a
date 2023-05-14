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
   using dict_type = Dictionary< Key, Value, Compare >;
   using iterator = ForwardListIterator< std::pair< Key, Value > >;
   using const_iterator = ConstForwardListIterator< std::pair< Key, Value > >;
  public:
   Dictionary():
     list_(),
     compare_()
   {}
   Dictionary(const dict_type& other):
     list_(other.list_),
     compare_(other.compare_)
   {}
   Dictionary(dict_type&& other):
     list_(std::move(other.list_)),
     compare_(other.compare_)
   {}
   ~Dictionary() = default;
   dict_type& operator=(const dict_type& other)
   {
     if (this != std::addressof(other))
     {
       list_ = other.list_;
       compare_ = other.compare_;
     }
     return *this;
   }
   dict_type& operator=(dict_type&& other)
   {
     if (this != std::addressof(other))
     {
       list_ = std::move(other.list_);
       compare_ = other.compare_;
     }
     return *this;
   }

   iterator begin()
   {
     return list_.begin();
   }
   iterator end()
   {
     return list_.end();
   }
   const_iterator cbegin() const
   {
     return list_.cbegin();
   }
   const_iterator cend() const
   {
     return list_.cend();
   }

   friend bool operator<(const dict_type& dict1, const dict_type& dict2)
   {
     auto iter = dict1.list_.cbegin();
     auto other_iter = dict2.list_.cbegin();
     return iter->first < other_iter->first;
   }

   friend std::ostream& operator<<(std::ostream& output, const dict_type& dict)
   {
     if (!dict.isEmpty())
     {
       auto iter = dict.list_.cbegin();
       output << iter->first << " " << iter->second;
       ++iter;
       while (iter != dict.list_.cend())
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
       auto iter_left = left.list_.cbegin();
       for (; iter_left != left.list_.cend(); iter_left++)
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
       auto iter_left = left.list_.cbegin();
       for (; iter_left != left.list_.cend(); iter_left++)
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
       auto iter_right = right.list_.cbegin();
       for (; iter_right != right.list_.cend(); iter_right++)
       {
         if (!left.find((*iter_right).first))
         {
           result.push((*iter_right).first, (*iter_right).second);
         }
       }
     }
     return result;
   }

   Value& at(const Key& key);
   const Value& at(const Key& key) const;
   void push(const Key& k, const Value& v);
   Value get(const Key& k) const;
   bool find(const Key& k) const;
   void remove(const Key& key);
   bool isEmpty() const;

  private:
   ForwardList< std::pair< Key, Value > > list_;
   Compare compare_;
  };

  template< typename Key, typename Value, typename Compare >
  Value& Dictionary< Key, Value, Compare >::at(const Key& key)
  {
    //...
    throw std::out_of_range("");
  }
  template< typename Key, typename Value, typename Compare >
  const Value& Dictionary< Key, Value, Compare >::at(const Key& key) const
  {
    //...
  }

  template< typename Key, typename Value, typename Compare >
  void Dictionary< Key, Value, Compare >::push(const Key& k, const Value& v)
  {
    std::pair< Key, Value > data(k, v);
    if (find(k))
    {
      remove(k);
    }
    auto prev = list_.cbeforeBegin();
    auto current = list_.cbegin();
    while (current != list_.cend() && compare_(*current, data))
    {
      ++prev;
      ++current;
    }
    list_.insertAfter(prev, data);
  };

  template< typename Key, typename Value, typename Compare >
  Value Dictionary< Key, Value, Compare >::get(const Key& k) const
  {
    if (!isEmpty())
    {
      auto current = list_.cbegin();
      while (current != list_.cend() && (k != current->first))
      {
        ++current;
      }
      if (current != list_.cend() && (k == current->first))
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
      auto current = list_.cbegin();
      while (current != list_.cend() && (k != current->first))
      {
        ++current;
      }
      if (current != list_.cend() && (k == current->first))
      {
        return true;
      }
    }
    return false;
  }

  template< typename Key, typename Value, typename Compare >
  void Dictionary< Key, Value, Compare >::remove(const Key& key)
  {
    auto prev = list_.cbeforeBegin();
    auto current = list_.cbegin();
    while (current != list_.end())
    {
      if (current->first == key)
      {
        ++current;
        list_.eraseAfter(prev);
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
    return list_.isEmpty();
  }
}
#endif
