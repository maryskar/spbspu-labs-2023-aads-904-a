#ifndef DICTIONARY_H
#define DICTIONARY_H
#include "iterator.h"
#include "citerator.h"
#include "forwardlist.h"

namespace skarlygina
{
  template < typename Key, typename Value, typename Compare = std::less< Key >>
  class Dictionary
  {
  public:
    Iterator< std::pair< Key, Value > > begin();
    Iterator< std::pair< Key, Value > > end();
    CIterator< std::pair< Key, Value > > begin() const;
    CIterator< std::pair< Key, Value > > end() const;
    CIterator< std::pair< Key, Value > > cbegin() const;
    CIterator< std::pair< Key, Value > > cend() const;

    Iterator< std::pair< Key, Value > > find(const Key&);
    CIterator< std::pair< Key, Value > > cfind(const Key&) const;

    void push(const Key&, const Value&);
    const Value& get(const Key&) const;
    void pop(const Key&);
    void clear();
    bool is_empty() const noexcept;
    bool is_equal(const Key& k1, const Key& k2) const noexcept;
  private:
    ForwardList< std::pair< Key, Value > > list_;
    Compare compare_;
  };

  template < typename Key, typename Value, typename Compare >
  bool Dictionary< Key, Value, Compare >::is_empty() const noexcept
  {
    return list_.isEmpty();
  }

  template < typename Key, typename Value, typename Compare >
  bool Dictionary<Key, Value, Compare>::is_equal(const Key& k1, const Key& k2) const noexcept
  {
    return !compare_(k1, k2) && !compare_(k2, k1);
  }

  template < typename Key, typename Value, typename Compare >
  void Dictionary<Key, Value, Compare>::push(const Key&, const Value&) {}

  template < typename Key, typename Value, typename Compare >
  const Value& Dictionary<Key, Value, Compare>::get(const Key&) const;

  template < typename Key, typename Value, typename Compare >
  void Dictionary<Key, Value, Compare>::pop(const Key&);

  template < typename Key, typename Value, typename Compare >
  void Dictionary<Key, Value, Compare>::clear();

  template < typename Key, typename Value, typename Compare >
  Iterator< std::pair< Key, Value > > Dictionary< Key, Value, Compare >::begin()
  {
    return list_.begin();
  }
  template < typename Key, typename Value, typename Compare >
  Iterator< std::pair< Key, Value > > Dictionary< Key, Value, Compare >::end()
  {
    return list_.end();
  }

  template < typename Key, typename Value, typename Compare >
  CIterator< std::pair< Key, Value > > Dictionary< Key, Value, Compare >::begin() const
  {
    return list_.begin();
  }
  template < typename Key, typename Value, typename Compare >
  CIterator< std::pair< Key, Value > > Dictionary< Key, Value, Compare >::end() const
  {
    return list_.end();
  }

  template < typename Key, typename Value, typename Compare >
  CIterator< std::pair< Key, Value > > Dictionary< Key, Value, Compare >::cbegin() const
  {
    return list_.cbegin();
  }
  template < typename Key, typename Value, typename Compare >
  CIterator< std::pair< Key, Value > > Dictionary< Key, Value, Compare >::cend() const
  {
    return list_.cend();
  }

  template < typename Key, typename Value, typename Compare >
  Iterator< std::pair< Key, Value > > Dictionary< Key, Value, Compare >::find(const Key& k)
  {
    auto const_it = cfind(k);
    return Iterator< std::pair< Key, Value > >(const_it);
  }
  template < typename Key, typename Value, typename Compare >
  CIterator< std::pair< Key, Value > > Dictionary< Key, Value, Compare >::cfind(const Key& k) const
  {
    CIterator< std::pair< Key, Value > > it = cbegin();
    Compare compare;
    while ((it != cend()) && (compare(it->first, k) || compare(k, it->first)))
    {
      ++it;
    }
    return it;
  }
}
#endif
