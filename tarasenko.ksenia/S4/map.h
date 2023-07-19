#ifndef MAP_H
#define MAP_H

#include <utility>
#include "RedBlackTree.h"

namespace tarasenko
{
  template< typename Key, typename Value, typename Compare >
  class Map
  {
   using map_t = Map< Key, Value, Compare >;
   using value_type = std::pair< Key, Value >;
   using iterator = BidirectionalIterator< value_type, Compare >;
   using const_iterator = ConstBidirectionalIterator< value_type, Compare >;
  public:
   Map():
     root_(),
     compare_()
   {}

   Map(const map_t& other):
     root_(other.root_),
     compare_(other.compare_)
   {}

   Map(map_t&& other):
     root_(std::move(other.root_)),
     compare_(other.compare_)
   {
     other.size_ = 0;
   }

   explicit Map(const Compare& comp):
     root_(comp),
     compare_(comp)
   {}

   ~Map() = default;

   map_t& operator=(const map_t& other)
   {
     if (this != std::addressof(other))
     {
       root_ = other.root_;
       compare_ = other.compare_;
     }
     return *this;
   }

   map_t& operator=(map_t&& other)
   {
     if (this != std::addressof(other))
     {
       root_ = std::move(other.root_);
       compare_ = other.compare_;
     }
     return *this;
   }

   iterator begin();
   iterator end();
   const_iterator cbegin() const;
   const_iterator cend() const;
//   reverse_iterator rbegin();
//   const_reverse_iterator crbegin() const;
//   reverse_iterator rend();
//   const_reverse_iterator crend() const;
   Value& at(const Key& key);
   const Value& at(const Key& key) const;
   Value& operator[](const Key& key);
   Value& operator[](Key&& key);
   bool isEmpty() const;
   size_t size() const;
   void clear();
   std::pair< iterator, bool > insert(const value_type& value);
   std::pair< iterator, bool > insert(value_type&& data);
   iterator insert(const_iterator pos, const value_type& data);
   iterator insert(const_iterator pos, value_type&& data);
   void insert(const_iterator first, const_iterator last);
   std::pair< iterator, bool > push(const Key& k, const Value& v);
   void swap(map_t& other);
   size_t count(const Key& key) const;
   iterator find(const Key& key);
   const_iterator find(const Key& key) const;
   iterator erase(iterator pos);
   iterator erase(const_iterator pos);
   iterator erase(const_iterator first, const_iterator last);
   size_t erase(const Key& key);
   bool isEqualTo(const map_t& other) const;
   Compare key_comp() const;
   iterator lower_bound(const Key& key);
   const_iterator lower_bound(const Key& key) const;
   iterator upper_bound(const Key& key);
   const_iterator upper_bound(const Key& key) const;

  private:
   RedBlackTree< std::pair< Key, Value >, Compare > root_;
   Compare compare_;
  };

  template< typename Key, typename Value, typename Compare >
  BidirectionalIterator< std::pair< Key, Value >, Compare > Map< Key, Value, Compare >::begin()
  {
    return root_.begin();
  }

  template< typename Key, typename Value, typename Compare >
  BidirectionalIterator< std::pair< Key, Value >, Compare > Map< Key, Value, Compare >::end()
  {
    return root_.end();
  }

  template< typename Key, typename Value, typename Compare >
  ConstBidirectionalIterator< std::pair< Key, Value >, Compare > Map< Key, Value, Compare >::cbegin() const
  {
    return root_.cbegin();
  }

  template< typename Key, typename Value, typename Compare >
  ConstBidirectionalIterator< std::pair< Key, Value >, Compare > Map< Key, Value, Compare >::cend() const
  {
    return root_.cend();
  }

  template< typename Key, typename Value, typename Compare >
  const Value& Map< Key, Value, Compare >::at(const Key& key) const
  {
    for (auto curr = cbegin(); curr != cend(); curr++)
    {
      if (curr->first == key)
      {
        return (*curr).second;
      }
    }
    throw std::out_of_range("Out of range!");
  }

  template< typename Key, typename Value, typename Compare >
  Value& Map< Key, Value, Compare >::at(const Key& key)
  {
    return const_cast< Value& >((static_cast< const map_t& >(*this)).at(key));
  }

  template< typename Key, typename Value, typename Compare >
  Value& Map< Key, Value, Compare >::operator[](const Key& key)
  {
    for (auto curr = cbegin(); curr != cend(); curr++)
    {
      if (curr->first == key)
      {
        return (*curr).second;
      }
    }
    auto res = root_.insert(std::make_pair(key, Value()));
    return res.first->second;
  }

  template< typename Key, typename Value, typename Compare >
  Value& Map< Key, Value, Compare >::operator[](Key&& key)
  {
    return (*this)[key];
  }

  template< typename Key, typename Value, typename Compare >
  bool Map< Key, Value, Compare >::isEmpty() const
  {
    return root_.isEmpty();
  }

  template< typename Key, typename Value, typename Compare >
  size_t Map< Key, Value, Compare >::size() const
  {
    return root_.size();
  }

  template< typename Key, typename Value, typename Compare >
  void Map< Key, Value, Compare >::clear()
  {
    root_.clear();
  }

  template< typename Key, typename Value, typename Compare >
  std::pair< BidirectionalIterator< std::pair< Key, Value >, Compare >, bool >
     Map< Key, Value, Compare >::insert(const std::pair< Key, Value >& value)
  {
    if (!isEmpty())
    {
      auto curr = begin();
      while (curr != end() && compare_(curr->first, value.first))
      {
        ++curr;
      }
      if (curr != end() && curr->first == value.first)
      {
        curr->second = value.second;
        return std::pair< iterator, bool >(curr, false);
      }
    }
    return root_.insert(value);
  }

  template< typename Key, typename Value, typename Compare >
  std::pair< BidirectionalIterator< std::pair< Key, Value >, Compare >, bool >
     Map< Key, Value, Compare >::insert(std::pair< Key, Value >&& value)
  {
    const value_type val(std::forward< value_type > >(value));
    return insert(val);
  }

  template< typename Key, typename Value, typename Compare >
  BidirectionalIterator< std::pair< Key, Value >, Compare >
     Map< Key, Value, Compare >::insert(const_iterator pos, const value_type& value)
  {
    return root_.insert(pos, value);
  }

  template< typename Key, typename Value, typename Compare >
  BidirectionalIterator< std::pair< Key, Value >, Compare >
     Map< Key, Value, Compare >::insert(const_iterator pos, value_type&& value)
  {
    const value_type val(std::forward< value_type >(value));
    return insert(pos, val);
  }

  template< typename Key, typename Value, typename Compare >
  void Map< Key, Value, Compare >::insert(const_iterator first, const_iterator last)
  {
    while (first != last)
    {
      insert(*first);
      first++;
    }
  }

  template< typename Key, typename Value, typename Compare >
  std::pair< BidirectionalIterator< std::pair< Key, Value >, Compare >, bool >
     Map< Key, Value, Compare >::push(const Key& k, const Value& v)
  {
    std::pair< Key, Value > data(k, v);
    return insert(data);
  };

  template< typename Key, typename Value, typename Compare >
  BidirectionalIterator< std::pair< Key, Value >, Compare >
     Map< Key, Value, Compare >::find(const Key& key)
  {
    if (!isEmpty())
    {
      for (auto curr = begin(); curr != end(); curr++)
      {
        if (curr->first == key)
        {
          return curr;
        }
      }
    }
    return end();
  }

  template< typename Key, typename Value, typename Compare >
  ConstBidirectionalIterator< std::pair< Key, Value >, Compare >
     Map< Key, Value, Compare >::find(const Key& key) const
  {
    return const_iterator(find(key));
  }

  template< typename Key, typename Value, typename Compare >
  BidirectionalIterator< std::pair< Key, Value >, Compare >
     Map< Key, Value, Compare >::erase(iterator pos)
  {
    return root_.erase(pos);
  }
  template< typename Key, typename Value, typename Compare >
  BidirectionalIterator< std::pair< Key, Value >, Compare >
     Map< Key, Value, Compare >::erase(const_iterator pos)
  {
    return root_.erase(pos);
  }
  template< typename Key, typename Value, typename Compare >
  BidirectionalIterator< std::pair< Key, Value >, Compare >
     Map< Key, Value, Compare >::erase(const_iterator first, const_iterator last)
  {
    return root_.erase(first, last);
  }

  template< typename Key, typename Value, typename Compare >
  size_t Map< Key, Value, Compare >::erase(const Key& key)
  {
    if (!isEmpty())
    {
      for (auto curr = cbegin(); curr != cend(); curr++)
      {
        if (curr->first == key)
        {
          root_.erase(curr);
          return 1;
        }
      }
    }
    return 0;
  }

  template< class Key, class Value, class Compare >
  void Map< Key, Value, Compare >::swap(map_t& other)
  {
    root_.swap(other.root_);
    std::swap(compare_, other.compare_);
  }

  template< class Key, class Value, class Compare >
  size_t Map< Key, Value, Compare >::count(const Key& key) const
  {
    if (!isEmpty())
    {
      for (auto curr = cbegin(); curr != cend(); curr++)
      {
        if (curr->first == key)
        {
          return 1;
        }
      }
    }
    return 0;
  }

  template< typename Key, typename Value, typename Compare >
  BidirectionalIterator< std::pair< Key, Value >, Compare >
     Map< Key, Value, Compare >::lower_bound(const Key& key)
  {
    auto curr = begin();
    while (curr != end())
    {
      if (!compare_(key, curr->first) && !compare_(curr->first, key))
      {
        return curr;
      }
      else if (compare_(key, curr->first))
      {
        --curr;
      }
      else
      {
        ++curr;
      }
    }
    return end();
  }

  template< typename Key, typename Value, typename Compare >
  ConstBidirectionalIterator< std::pair< Key, Value >, Compare >
     Map< Key, Value, Compare >::lower_bound(const Key& key) const
  {
    return const_iterator(lower_bound(key));
  }

  template< typename Key, typename Value, typename Compare >
  BidirectionalIterator< std::pair< Key, Value >, Compare >
     Map< Key, Value, Compare >::upper_bound(const Key& key)
  {
    iterator it = lower_bound(key);
    if (it == end())
    {
      return end();
    }
    else
    {
      if (!compare_(it->first, key) && !compare_(key, it->first))
      {
        return ++it;
      }
      else
      {
        return it;
      }
    }
  }

  template< typename Key, typename Value, typename Compare >
  ConstBidirectionalIterator< std::pair< Key, Value >, Compare >
     Map< Key, Value, Compare >::upper_bound(const Key& key) const
  {
    return const_iterator(upper_bound(key));
  }

  template< class Key, class Value, class Compare >
  Compare Map< Key, Value, Compare >::key_comp() const
  {
    return compare_;
  }

  template< class Key, class Value, class Compare >
  bool Map< Key, Value, Compare >::isEqualTo(const Map< Key, Value, Compare >& other) const
  {
    return root_ == other.root_;
  }

  template< class Key, class Value, class Compare >
  bool operator==(const Map< Key, Value, Compare >& lhs, const Map< Key, Value, Compare >& rhs)
  {
    return lhs.isEqualTo(rhs);
  }

  template< class Key, class Value, class Compare >
  bool operator!=(const Map< Key, Value, Compare >& lhs, const Map< Key, Value, Compare >& rhs)
  {
    return !(lhs == rhs);
  }
}
#endif
