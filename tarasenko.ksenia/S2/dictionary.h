#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <stdexcept>
#include <forward_list.h>
#include <sort.h>

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

   explicit Dictionary(const Compare& comp):
     list_(),
     size_(0),
     compare_(comp)
   {}

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

   Value& at(const Key& key);
   const Value& at(const Key& key) const;
   Value& operator[](const Key& key);
   Value& operator[](Key&& key);
   bool isEmpty() const;
   size_t size() const;
   void clear();
   std::pair< iterator, bool > insert(const std::pair< Key, Value >& value);
   std::pair< iterator, bool > push(const Key& k, const Value& v);
   void swap(dict_type& other);
   size_t count(const Key& key) const;
   const_iterator find(const Key& key) const;
   size_t remove(const Key& key);
   Compare key_comp() const;
   void setCompare(Compare comp);

  private:
   ForwardList< std::pair< Key, Value > > list_;
   size_t size_;
   Compare compare_;
  };

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
  Value& Dictionary< Key, Value, Compare >::at(const Key& key)
  {
    return const_cast< Value& >((static_cast< const dict_type& >(*this)).at(key));
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
    if (curr != list_.end() && (*curr).first == value.first)
    {
      (*curr).second = value.second;
      return std::pair< iterator, bool >(curr, false);
    }
    else
    {
      list_.insertAfter(prev, value);
      ++size_;
      return std::pair< iterator, bool >(++prev, true);
    }
  }

  template< typename Key, typename Value, typename Compare >
  std::pair< ForwardListIterator< std::pair< Key, Value > >, bool >
  Dictionary< Key, Value, Compare >::push(const Key& k, const Value& v)
  {
    std::pair< Key, Value > data(k, v);
    return insert(data);
  }

  template< typename Key, typename Value, typename Compare >
  ConstForwardListIterator< std::pair< Key, Value > > Dictionary< Key, Value, Compare >::find(const Key& k) const
  {
    auto curr = cbegin();
    while (curr != cend())
    {
      if (k == curr->first)
      {
        return curr;
      }
      ++curr;
    }
    return cend();
  }

  template< typename Key, typename Value, typename Compare >
  size_t Dictionary< Key, Value, Compare >::remove(const Key& key)
  {
    auto prev = list_.cbeforeBegin();
    auto curr = list_.cbegin();
    while (curr != list_.end())
    {
      if (curr->first == key)
      {
        list_.eraseAfter(prev);
        --size_;
        return 1;
      }
      ++curr;
      ++prev;
    }
    return 0;
  }

  template< class Key, class Value, class Compare >
  void Dictionary< Key, Value, Compare >::swap(dict_type& other)
  {
    list_.swap(other.list_);
  }

  template< class Key, class Value, class Compare >
  size_t Dictionary< Key, Value, Compare >::count(const Key& key) const
  {
    auto curr = cbegin();
    while (curr != cend())
    {
      if (curr->first == key)
      {
        return 1;
      }
      ++curr;
    }
    return 0;
  }

  template< typename Key, typename Value, typename Compare >
  Compare Dictionary< Key, Value, Compare >::key_comp() const
  {
    return compare_;
  }

  template< typename Key, typename Value, typename Compare >
  void Dictionary< Key, Value, Compare >::setCompare(Compare comp)
  {
    compare_ = comp;
    quickSort(list_.begin(), list_.end(), compare_);
  }

  template< class Key, class Value, class Compare >
  bool operator==(const Dictionary< Key, Value, Compare >& lhs, const Dictionary< Key, Value, Compare >& rhs)
  {
    auto lhs_iter = lhs.cbegin();
    auto rhs_iter = rhs.cbegin();
    while (lhs_iter != lhs.cend() && rhs_iter != rhs.cend())
    {
      if (*lhs_iter != *rhs_iter)
      {
        return false;
      }
      ++lhs_iter;
      ++rhs_iter;
    }
    return true;
  }

  template< class Key, class Value, class Compare >
  bool operator!=(const Dictionary< Key, Value, Compare >& lhs, const Dictionary< Key, Value, Compare >& rhs)
  {
    return !(lhs == rhs);
  }
}
#endif
