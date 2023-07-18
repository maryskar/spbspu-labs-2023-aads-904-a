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
     size_(0),
     compare_()
   {}

   Map(const map_t& other):
     root_(other.root_),
     size_(other.size_),
     compare_(other.compare_)
   {}

   Map(map_t&& other):
     root_(std::move(other.root_)),
     size_(other.size_),
     compare_(other.compare_)
   {
     other.size_ = 0;
   }

   ~Map() = default;

   map_t& operator=(const map_t& other)
   {
     if (this != std::addressof(other))
     {
       root_ = other.root_;
       size_ = other.size_;
       compare_ = other.compare_;
     }
     return *this;
   }

   map_t& operator=(map_t&& other)
   {
     if (this != std::addressof(other))
     {
       root_ = std::move(other.root_);
       size_ = other.size_;
       compare_ = other.compare_;
       other.size_ = 0;
     }
     return *this;
   }

   iterator begin()
   {
     return root_.begin();
   }

   iterator end()
   {
     return root_.end();
   }

   const_iterator cbegin() const
   {
     return root_.cbegin();
   }

   const_iterator cend() const
   {
     return root_.cend();
   }

   Value& at(const Key& key);
   const Value& at(const Key& key) const;
   Value& operator[](const Key& key);
   Value& operator[](Key&& key);
   bool isEmpty() const;
   size_t size() const;
   void clear();
   std::pair< iterator, bool > insert(const value_type& value);
   std::pair< iterator, bool > push(const Key& k, const Value& v);
   void swap(map_t& other);
   size_t count(const Key& key) const;
   const_iterator find(const Key& key) const;
   size_t remove(const Key& key);
   bool isEqualTo(const map_t& other) const;

  private:
   RedBlackTree< std::pair< Key, Value >, Compare > root_;
   size_t size_;
   Compare compare_;
  };

  template< typename Key, typename Value, typename Compare >
  Value& Map< Key, Value, Compare >::at(const Key& key)
  {

  }

  template< typename Key, typename Value, typename Compare >
  const Value& Map< Key, Value, Compare >::at(const Key& key) const
  {

  }

  template< typename Key, typename Value, typename Compare >
  Value& Map< Key, Value, Compare >::operator[](const Key& key)
  {

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
    return size_;
  }

  template< typename Key, typename Value, typename Compare >
  void Map< Key, Value, Compare >::clear()
  {
    root_.clear();
    size_ = 0;
  }

  template< typename Key, typename Value, typename Compare >
  std::pair< BidirectionalIterator< std::pair< Key, Value >, Compare >, bool >
     Map< Key, Value, Compare >::insert(const std::pair< Key, Value >& value)
  {

  }

  template< typename Key, typename Value, typename Compare >
  std::pair< BidirectionalIterator< std::pair< Key, Value >, Compare >, bool >
     Map< Key, Value, Compare >::push(const Key& k, const Value& v)
  {
    std::pair< Key, Value > data(k, v);
    return insert(data);
  };

  template< typename Key, typename Value, typename Compare >
  ConstBidirectionalIterator< std::pair< Key, Value >, Compare > Map< Key, Value, Compare >::find(const Key& k) const
  {

  }

  template< typename Key, typename Value, typename Compare >
  size_t Map< Key, Value, Compare >::remove(const Key& key)
  {

  }

  template< class Key, class Value, class Compare >
  void Map< Key, Value, Compare >::swap(map_t& other)
  {
    root_.swap(other.root_);
  }

  template< class Key, class Value, class Compare >
  size_t Map< Key, Value, Compare >::count(const Key& key) const
  {

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
