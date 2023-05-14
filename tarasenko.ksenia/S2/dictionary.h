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
     size_(0),
     compare_()
   {}
   Dictionary(const dict_type& other):
     list_(other.list_),
     size_(other.size_),
     compare_(other.compare_)
   {}
   Dictionary(dict_type&& other):
     list_(std::move(other.list_)),
     size_(other.size_),
     compare_(other.compare_)
   {
     other.size_ = 0;
   }
   ~Dictionary() = default;
   dict_type& operator=(const dict_type& other)
   {
     if (this != std::addressof(other))
     {
       list_ = other.list_;
       size_ = other.size_;
       compare_ = other.compare_;
     }
     return *this;
   }
   dict_type& operator=(dict_type&& other)
   {
     if (this != std::addressof(other))
     {
       list_ = std::move(other.list_);
       size_ = other.size_;
       compare_ = other.compare_;
       other.size_ = 0;
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
   Value& operator[](const Key& key);
   Value& operator[](Key&& key);
   bool isEmpty() const;
   size_t size() const;
   void clear();
   std::pair< iterator, bool > insert(const std::pair< Key, Value >& value);
   //iterator erase(const_iterator pos);
   std::pair< iterator, bool > push(const Key& k, const Value& v);
   //void swap(dict_type& other);
   //size_t count(const Key& key) const;
   //const_iterator find( const Key& key ) const;
   Value get(const Key& k) const;
   bool find(const Key& k) const;
   void remove(const Key& key);

  private:
   ForwardList< std::pair< Key, Value > > list_;
   size_t size_;
   Compare compare_;
  };

  template< typename Key, typename Value, typename Compare >
  Value& Dictionary< Key, Value, Compare >::at(const Key& key)
  {
    auto curr = begin();
    while (curr != end())
    {
      if ((*curr).first == key)
      {
        return (*curr).second;
      }
      ++curr;
    }
    throw std::out_of_range("Out of range!");
  }

  template< typename Key, typename Value, typename Compare >
  const Value& Dictionary< Key, Value, Compare >::at(const Key& key) const
  {
    auto curr = cbegin();
    while (curr != cend())
    {
      if ((*curr).first == key)
      {
        return (*curr).second;
      }
      ++curr;
    }
    throw std::out_of_range("Out of range!");
  }

  template< typename Key, typename Value, typename Compare >
  Value& Dictionary< Key, Value, Compare >::operator[](const Key& key)
  {
    auto prev = list_.beforeBegin();
    auto curr = begin();
    while (curr != end())
    {
      if ((*curr).first == key)
      {
        return (*curr).second;
      }
      prev = curr;
      ++curr;
    }
    auto res = list_.insertAfter(prev, std::pair< Key, Value >(key, Value()));
    return (*res).second;
  }

  template< typename Key, typename Value, typename Compare >
  Value& Dictionary< Key, Value, Compare >::operator[](Key&& key)
  {
    return (*this)[key];
  }

  template< typename Key, typename Value, typename Compare >
  bool Dictionary< Key, Value, Compare >::isEmpty() const
  {
    return list_.isEmpty();
  }

  template< typename Key, typename Value, typename Compare >
  size_t Dictionary< Key, Value, Compare >::size() const
  {
    return size_;
  }

  template< typename Key, typename Value, typename Compare >
  void Dictionary< Key, Value, Compare >::clear()
  {
    list_.clear();
    size_ = 0;
  }

  template< typename Key, typename Value, typename Compare >
  std::pair< ForwardListIterator< std::pair< Key, Value > >, bool >
      Dictionary< Key, Value, Compare >::insert(const std::pair< Key, Value >& value)
  {
    auto prev = list_.beforeBegin();
    auto curr = list_.begin();
    while (curr != list_.end() && compare_((*curr).first, value.first))
    {
      ++prev;
      ++curr;
    }
    if (prev != list_.beforeBegin() && (*prev).first == value.first)
    {
      (*prev).second = value.second;
      return std::pair< iterator, bool >(iterator(prev), false);
    }
    else
    {
      list_.insertAfter(prev, value);
      ++size_;
      return std::pair< iterator, bool >(iterator(prev), true);
    }
  }

  template< typename Key, typename Value, typename Compare >
  std::pair< ForwardListIterator< std::pair< Key, Value > >, bool >
      Dictionary< Key, Value, Compare >::push(const Key& k, const Value& v)
  {
    std::pair< Key, Value > data(k, v);
    return insert(data);
  };

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
    --size_;
  }

  template< class Key, class T, class Compare >
  bool operator==( const Dictionary<Key, T, Compare >& lhs, const Dictionary<Key, T, Compare >& rhs );
  template< class Key, class T, class Compare, class Alloc >
  bool operator!=( const Dictionary<Key, T, Compare >& lhs, const Dictionary<Key, T, Compare >& rhs );
}
#endif
