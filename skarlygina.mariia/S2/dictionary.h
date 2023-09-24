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
  void Dictionary<Key, Value, Compare>::push(const Key& k, const Value& v)
  {
    if (list_.isEmpty())
    {
      list_.pushBack(std::pair< Key, Value >{k, v});
      return;
    }
    Compare compare;
    auto it = list_.cbegin();
    if (compare(k, it->first))
    {
      list_.pushFront(std::pair< Key, Value >{k, v});
      return;
    }
    else if (!compare(k, it->first) && !compare(it->first, k))
    {
      list_.popFront();
      list_.pushFront(std::pair< Key, Value >{k, v});
      return;
    }
    auto it_next = ++list_.cbegin();
    while ((it_next != list_.cend()) && compare(it_next->first, k))
    {
      ++it_next;
      ++it;
    }
    if (it_next == list_.cend())
    {
      list_.pushBack(std::pair< Key, Value >{k, v});
    }
    else if ((it_next != list_.cend()) && !compare(k, it_next->first) && !compare(it_next->first, k))
    {
      list_.eraseAfter(it);
      list_.insertAfter(it, std::pair< Key, Value >{k, v});
    }
    else
    {
      list_.insertAfter(it, std::pair< Key, Value >{k, v});
    }
  }

  template < typename Key, typename Value, typename Compare >
  const Value& Dictionary<Key, Value, Compare>::get(const Key& k) const
  {
    auto it = list_.cbegin();
    while (it != cend())
    {
      if (!Compare()(it->first, k) && !Compare()(k, it->first))
      {
        return it->second;
      }
      it++;
    }
    throw std::invalid_argument("Function can't get value");
  }

  template < typename Key, typename Value, typename Compare >
  void Dictionary<Key, Value, Compare>::pop(const Key& k)
  {
    auto it = list_.cbegin();
    auto next_it = ++list_.cbegin();
    Compare compare;
    if (!compare(it->first, k) && !cmp(k, it->first))
    {
      list_.popFront();
      return;
    }
    while ((it != list_.cend()) && (compare(next_it->first, k) || compare(k, next_it->first)))
    {
      ++next_it;
      ++it;
    }
    if (it == list_.cend())
    {
      throw std::logic_error("No such key!\n");
    }
    else
    {
      list_.eraseAfter(it);
    }
  }

  template < typename Key, typename Value, typename Compare >
  void Dictionary<Key, Value, Compare>::clear()
  {
    list_.clear();
  }

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
