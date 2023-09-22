#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <stdexcept>
#include "Forwardlist.h"

namespace chulkov {
  template < typename Key, typename Value, typename Compare = std::less< Key > >
  class Dictionary
  {
  public:
    using Iter = ForwardIter< std::pair< Key, Value > >;
    using CIter = ForwardConstIter< std::pair< Key, Value > >;
    Dictionary() = default;
    Dictionary(const Dictionary& dict) = default;
    Dictionary(Dictionary&& dict) = default;
    ~Dictionary() = default;

    Dictionary& operator=(const Dictionary& dict) = default;
    Dictionary& operator=(Dictionary&& dict) = default;

    void push(const Key&, const Value&);
    const Value& get(const Key&) const;
    void pop(const Key& key);
    void clear();
    bool isEmpty() const noexcept;

    Iter find(const Key&);
    Iter begin();
    Iter end();
    CIter cbegin() const;
    CIter cend() const;
    CIter cfind(const Key&) const;

  private:
    Compare cmp;
    FrdList< std::pair< Key, Value > > list_;
    bool isEqual(const Key& first, const Key& second) const;
  };

  template < typename Key, typename Value, typename Compare >
  bool Dictionary< Key, Value, Compare >::isEqual(const Key& first, const Key& second) const
  {
    return (!cmp(first, second)) && (!cmp(second, first));
  }

  template < typename Key, typename Value, typename Compare >
  void Dictionary< Key, Value, Compare >::push(const Key& k, const Value& v)
  {
    if (list_.isEmpty()) {
      list_.pushBack(std::pair< Key, Value >{k, v});
      return;
    }
    Compare cmp;
    auto it = list_.cbegin();
    if (cmp(k, it->first)) {
      list_.pushFront(std::pair< Key, Value >{k, v});
      return;
    } else if (!cmp(k, it->first) && !cmp(it->first, k)) {
      list_.popFront();
      list_.pushFront(std::pair< Key, Value >{k, v});
      return;
    }
    auto itNext = ++list_.cbegin();
    while ((itNext != list_.cend()) && cmp(itNext->first, k)) {
      ++itNext;
      ++it;
    }
    if (itNext == list_.cend()) {
      list_.pushBack(std::pair< Key, Value >{k, v});
    } else if ((itNext != list_.cend()) && !cmp(k, itNext->first) && !cmp(itNext->first, k)) {
      list_.eraseAfter(it);
      list_.insertAfter(it, std::pair< Key, Value >{k, v});
    } else {
      list_.insertAfter(it, std::pair< Key, Value >{k, v});
    }
  }

  template < typename Key, typename Value, typename Compare >
  const Value& Dictionary< Key, Value, Compare >::get(const Key& k) const
  {
    auto i = cbegin();
    i = find(k);
    if (i == cend()) {
      throw std::out_of_range("Out of range");
    }
    return i->second;
  }

  template < typename Key, typename Value, typename Compare >
  void Dictionary< Key, Value, Compare >::pop(const Key& k)
  {
    auto it = list_.cbegin();
    auto nextIt = ++list_.cbegin();
    Compare cmp;
    if (!cmp(it->first, k) && !cmp(k, it->first)) {
      list_.popFront();
      return;
    }
    while ((it != list_.cend()) && (cmp(nextIt->first, k) || cmp(k, nextIt->first))) {
      ++nextIt;
      ++it;
    }
    if (it == list_.cend()) {
      throw std::logic_error("No such key!\n");
    } else {
      list_.eraseAfter(it);
    }
  }

  template < typename Key, typename Value, typename Compare >
  ForwardIter< std::pair< Key, Value > > Dictionary< Key, Value, Compare >::find(const Key& k)
  {
    auto constIt = cfind(k);
    return ForwardIter< std::pair< Key, Value > >(constIt);
  }

  template < typename Key, typename Value, typename Compare >
  ForwardConstIter< std::pair< Key, Value > > Dictionary< Key, Value, Compare >::cfind(const Key& k) const
  {
    ForwardConstIter< std::pair< Key, Value > > it = cbegin();
    Compare cmp;
    while ((it != cend()) && (cmp(it->first, k) || cmp(k, it->first))) {
      ++it;
    }
    return it;
  }
}

#endif
