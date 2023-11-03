#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <stdexcept>
#include "ForwardList.h"

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
    Value& operator[](const Key& k);
    const Value& operator[](const Key& k) const;

    void push(const Key&, const Value&);
    Value& get(const Key& k);
    void pop(const Key& key);
    void clear();
    bool isEmpty() const noexcept;
    bool contains(const Key& key) const;

    Iter find(const Key&);
    Iter begin() const;
    Iter end() const;
    CIter cbegin() const;
    CIter cend() const;
    CIter cfind(const Key&) const;

  private:
    Compare cmp;
    ForwardList< std::pair< Key, Value > > list_;
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
  Value& Dictionary< Key, Value, Compare >::get(const Key& k) {
    auto i = find(k);
    if (i == end()) {
      throw std::out_of_range("Key not found");
    }
    return i->second;
  }

  template < typename Key, typename Value, typename Compare >
  bool Dictionary< Key, Value, Compare >::contains(const Key& key) const
  {
    for (const auto& pair : list_) {
      if (isEqual(pair.first, key)) {
        return true;
      }
    }
    return false;
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
      throw std::logic_error("No such key");
    } else {
      list_.eraseAfter(it);
    }
  }

  template < typename Key, typename Value, typename Compare >
  Value& Dictionary< Key, Value, Compare >::operator[](const Key& k) {
    auto i = cfind(k);
    if (i == cend()) {
      push(k, Value());
      i = cfind(k);
    }
    return i->second;
  }

  template < typename Key, typename Value, typename Compare >
  const Value& Dictionary< Key, Value, Compare >::operator[](const Key& k) const {
    auto i = cfind(k);
    if (i == cend()) {
      throw std::out_of_range("Key not found");
    }
    return i->second;
  }

  template < typename Key, typename Value, typename Compare >
  ForwardIter< std::pair< Key, Value > > Dictionary< Key, Value, Compare >::find(const Key& k)
  {
    auto i = begin();
    for (; i != end(); i++) {
      if (!cmp(i->first, k)) {
        break;
      }
    }
    if (i == end() || cmp(k, i->first)) {
      return end();
    }
    return i;
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

  template < typename Key, typename Value, typename Compare > void Dictionary< Key, Value, Compare >::clear()
  {
    list_.clear();
  }

  template < typename Key, typename Value, typename Compare >
  ForwardIter< std::pair< Key, Value > > Dictionary< Key, Value, Compare >::begin() const
  {
    return list_.begin();
  }

  template < typename Key, typename Value, typename Compare >
  bool Dictionary< Key, Value, Compare >::isEmpty() const noexcept
  {
    return list_.isEmpty();
  }

  template < typename Key, typename Value, typename Compare >
  ForwardIter< std::pair< Key, Value > > Dictionary< Key, Value, Compare >::end() const
  {
    return list_.end();
  }

  template < typename Key, typename Value, typename Compare >
  ForwardConstIter< std::pair< Key, Value > > Dictionary< Key, Value, Compare >::cbegin() const
  {
    return list_.cbegin();
  }

  template < typename Key, typename Value, typename Compare >
  ForwardConstIter< std::pair< Key, Value > > Dictionary< Key, Value, Compare >::cend() const
  {
    return list_.cend();
  }
}

#endif
