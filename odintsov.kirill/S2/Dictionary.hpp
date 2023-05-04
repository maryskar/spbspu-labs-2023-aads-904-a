#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <functional>
#include <initializer_list>
#include <memory>
#include <stdexcept>
#include <utility>

#include "ForwardList.hpp"

namespace odintsov {
  template< typename Key, typename Value, typename Compare = std::less< Key > >
  class Dictionary {
   public:
    using kvPair = std::pair< const Key, Value >;
    using Iter = typename ForwardList< kvPair >::Iter;
    using ConstIter = typename ForwardList< kvPair >::ConstIter;
    using ListNode = typename ForwardList< kvPair >::Node;

    struct KVComp {
      Compare keyComp;

      bool operator()(const kvPair& lhs, const kvPair& rhs)
      {
        return keyComp(lhs.first, rhs.first);
      }
    };

    Dictionary():
      kvComp_{Compare()}
    {}

    Dictionary(const Dictionary& d) = default;

    Dictionary(Dictionary&& d) = default;

    explicit Dictionary(std::initializer_list< kvPair > il, const Compare& comp = Compare()):
      pairs_(il),
      kvComp_{comp}
    {
      pairs_.sort();
    }

    explicit Dictionary(const Compare& comp):
      kvComp_{comp}
    {}

    Dictionary& operator=(const Dictionary& d)
    {
      if (this == std::addressof(d)) {
        return *this;
      }
      pairs_ = d.pairs_;
      kvComp_ = d.kvComp_;
      return *this;
    }

    Dictionary& operator=(Dictionary&& d)
    {
      pairs_ = std::move(d.pairs_);
      kvComp_ = std::move(d.kvComp_);
      return *this;
    }

    Dictionary& operator=(std::initializer_list< kvPair > il)
    {
      pairs_ = ForwardList< kvPair >(il);
      pairs_.sort(kvComp_);
    }

    Value& at(const Key& k)
    {
      return const_cast< Value& >(const_cast< const Dictionary* >(this)->at(k));
    }

    const Value& at(const Key& k) const
    {
      ConstIter pos = find(k);
      if (pos == cend()) {
        throw std::out_of_range("Invalid key");
      }
      return pos->second;
    }

    Value& operator[](const Key& k)
    {
      ConstIter plb = preLowerBound(k);
      if (plb->next->val.first == k) {
        return plb->next->val.second;
      }
      return pairs_.unsafeInsertAfter(plb, std::make_pair(k, Value()))->second;
    }

    Value& operator[](Key&& k)
    {
      ConstIter plb = preLowerBound(k);
      if (plb->next->val.first == k) {
        return plb->next->val.second;
      }
      return pairs_.unsafeInsertAfter(plb, std::make_pair(std::move(k), Value()))->second;
    }

    Iter beforeBegin()
    {
      return pairs_.beforeBegin();
    }

    ConstIter cbeforeBegin() const
    {
      return pairs_.cbeforeBegin();
    }

    Iter begin()
    {
      return pairs_.begin();
    }

    ConstIter cbegin() const
    {
      return pairs_.cbegin();
    }

    Iter end()
    {
      return pairs_.end();
    }

    ConstIter cend() const
    {
      return pairs_.cend();
    }

    bool empty() const
    {
      return pairs_.empty();
    }

    void clear()
    {
      return pairs_.clear();
    }

    template< typename V >
    std::pair< Iter, bool > insert(const Key& k, V&& val)
    {
      return insert(cbegin(), std::make_pair(k, Value(std::forward< V >(val))));
    }

    template< typename V >
    std::pair< Iter, bool > insert(Key&& k, V&& val)
    {
      return insert(cbegin(), std::make_pair(std::move(k), Value(std::forward< V >(val))));
    }

    std::pair< Iter, bool > insert(const kvPair& kv)
    {
      return insert(cbegin(), kv);
    }

    std::pair< Iter, bool > insert(kvPair&& kv)
    {
      return insert(cbegin(), std::move(kv));
    }

    template< typename V >
    std::pair< Iter, bool > insert(ConstIter pos, const Key& k, V&& val)
    {
      return insert(pos, std::make_pair(k, Value(std::forward< V >(val))));
    }

    template< typename V >
    std::pair< Iter, bool > insert(ConstIter pos, Key&& k, V&& val)
    {
      return insert(pos, std::make_pair(std::move(k), Value(std::forward< V >(val))));
    }

    std::pair< Iter, bool > insert(ConstIter pos, const kvPair& kv)
    {
      Iter plb = preLowerBound(pos, kv.first);
      bool insert = plb.nodePtr->next->val.first != kv.first;
      if (insert) {
        plb = pairs_.unsafeInsertAfter(plb, kv);
      } else {
        ++plb;
      }
      return std::make_pair(plb, insert);
    }

    std::pair< Iter, bool > insert(ConstIter pos, kvPair&& kv)
    {
      Iter plb = preLowerBound(pos, kv.first);
      bool insert = plb.nodePtr->next->val.first != kv.first;
      if (insert) {
        plb = pairs_.unsafeInsertAfter(plb, std::move(kv));
      } else {
        ++plb;
      }
      return std::make_pair(plb, insert);
    }

    template< class InputIter >
    void insert(InputIter first, InputIter last)
    {
      ConstIter lastPos = cbegin();
      for (; first != last; ++first) {
        lastPos = insert(kvComp_.keyComp(lastPos->first, first->first) ? lastPos : cbegin(), first->second).first;
      }
    }

    void insert(std::initializer_list< kvPair > il)
    {
      insert(il.begin(), il.end());
    }

    template< typename V >
    std::pair< Iter, bool > insertOrAssign(const Key& k, V&& val)
    {
      return insertOrAssign(cbegin(), std::make_pair(k, Value(std::forward< V >(val))));
    }

    template< typename V >
    std::pair< Iter, bool > insertOrAssign(Key&& k, V&& val)
    {
      return insertOrAssign(cbegin(), std::make_pair(std::move(k), Value(std::forward< V >(val))));
    }

    std::pair< Iter, bool > insertOrAssign(const kvPair& kv)
    {
      return insertOrAssign(cbegin(), kv);
    }

    std::pair< Iter, bool > insertOrAssign(kvPair&& kv)
    {
      return insertOrAssign(cbegin(), std::move(kv));
    }

    template< typename V >
    std::pair< Iter, bool > insertOrAssign(ConstIter pos, const Key& k, V&& val)
    {
      return insertOrAssign(pos, std::make_pair(k, Value(std::forward< V >(val))));
    }

    template< typename V >
    std::pair< Iter, bool > insertOrAssign(ConstIter pos, Key&& k, V&& val)
    {
      return insertOrAssign(pos, std::make_pair(std::move(k), Value(std::forward< V >(val))));
    }

    std::pair< Iter, bool > insertOrAssign(ConstIter pos, const kvPair& kv)
    {
      std::pair< Iter, bool > res = insert(pos, kv);
      if (!res.second) {
        *res.first = kv;
      }
      return res;
    }

    std::pair< Iter, bool > insertOrAssign(ConstIter pos, kvPair&& kv)
    {
      std::pair< Iter, bool > res = insert(pos, std::move(kv));
      if (!res.second) {
        *res.first = std::move(kv);
      }
      return res;
    }

    template< typename... Args >
    std::pair< Iter, bool > emplace(Args&&... args)
    {
      return insert(std::make_pair(std::forward< Args >(args)...));
    }

    template< typename... Args >
    std::pair< Iter, bool > emplace(ConstIter pos, Args&&... args)
    {
      return insert(pos, std::make_pair(std::forward< Args >(args)...));
    }

    template< typename... Args >
    std::pair< Iter, bool > tryEmplace(const Key& k, Args&&... args)
    {
      return insert(std::make_pair(k, Value(std::forward< Args >(args)...)));
    }

    template< typename... Args >
    std::pair< Iter, bool > tryEmplace(Key&& k, Args&&... args)
    {
      return insert(std::make_pair(std::move(k), Value(std::forward< Args >(args)...)));
    }

    template< typename... Args >
    std::pair< Iter, bool > tryEmplace(ConstIter pos, const Key& k, Args&&... args)
    {
      return insert(pos, std::make_pair(k, Value(std::forward< Args >(args)...)));
    }

    template< typename... Args >
    std::pair< Iter, bool > tryEmplace(ConstIter pos, Key&& k, Args&&... args)
    {
      return insert(pos, std::make_pair(std::move(k), Value(std::forward< Args >(args)...)));
    }

    Iter eraseAfter(ConstIter pos)
    {
      return pairs_.eraseAfter(pos);
    }

    Iter eraseAfter(ConstIter first, ConstIter last)
    {
      return pairs_.eraseAfter(first, last);
    }

    bool erase(const Key& k)
    {
      ConstIter prev = cbegin();
      while (kvComp_.keyComp(prev.nodePtr->next->val.first, k)) {
        ++prev;
      }
      if (prev.nodePtr->next->val.first == k) {
        pairs_.unsafeEraseAfter(prev);
        return true;
      }
      return false;
    }

    void swap(Dictionary& d)
    {
      std::swap(pairs_, d.pairs_);
    }

    template< typename C >
    void merge(Dictionary< Key, Value, C >& src)
    {
      ConstIter pos = beforeBegin();
      for (Iter siter = src.beforeBegin(); siter.nodePtr->next != nullptr; ++siter) {
        bool inserted = false;
        ListNode* snext = siter.nodePtr->next;
        if (kvComp_.keyComp(snext->val.first, pos->first)) {
          pos = beforeBegin();
        }
        while (kvComp_.keyComp(pos.nodePtr->next->val.first, snext->val.first)) {
          ++pos;
        }
        if (pos.nodePtr->next->val.first != snext->val.first) {
          siter.nodePtr->next = snext->next;
          snext->next = pos.nodePtr->next;
          pos.nodePtr->next = snext;
        }
      }
    }

    template< typename C >
    void merge(Dictionary< Key, Value, C >&& src)
    {
      merge(src);
    }

    Iter find(const Key& k)
    {
      return Iter(const_cast< ListNode* >(const_cast< const Dictionary* >(this)->find(k).nodePtr));
    }

    ConstIter find(const Key& k) const
    {
      ConstIter lb = lowerBound(k);
      if (lb->first != k) {
        return cend();
      }
      return lb;
    }

    bool contains(const Key& k) const
    {
      return find(k) != cend();
    }

    Iter preLowerBound(const Key& k)
    {
      return Iter(const_cast< ListNode* >(const_cast< const Dictionary* >(this)->preLowerBound(k).nodePtr));
    }

    Iter preLowerBound(ConstIter pos, const Key& k)
    {
      return Iter(const_cast< ListNode* >(const_cast< const Dictionary* >(this)->preLowerBound(pos, k).nodePtr));
    }

    ConstIter preLowerBound(const Key& k) const
    {
      return preLowerBound(cbeforeBegin(), k);
    }

    ConstIter preLowerBound(ConstIter pos, const Key& k) const
    {
      while (kvComp_.keyComp(pos->next->val.first, k)) {
        ++pos;
      }
      return pos;
    }

    Iter lowerBound(const Key& k)
    {
      return Iter(const_cast< ListNode* >(const_cast< const Dictionary* >(this)->lowerBound(k).nodePtr));
    }

    Iter lowerBound(ConstIter pos, const Key& k)
    {
      return Iter(const_cast< ListNode* >(const_cast< const Dictionary* >(this)->lowerBound(pos, k).nodePtr));
    }

    ConstIter lowerBound(const Key& k) const
    {
      return lowerBound(cbegin(), k);
    }

    ConstIter lowerBound(ConstIter pos, const Key& k) const
    {
      while (kvComp_.keyComp(pos->first, k)) {
        ++pos;
      }
      return pos;
    }

    Iter upperBound(const Key& k)
    {
      return Iter(const_cast< ListNode* >(const_cast< const Dictionary* >(this)->upperBound(k).nodePtr));
    }

    Iter upperBound(ConstIter pos, const Key& k)
    {
      return Iter(const_cast< ListNode* >(const_cast< const Dictionary* >(this)->upperBound(pos, k).nodePtr));
    }

    ConstIter upperBound(const Key& k) const
    {
      return upperBound(cbegin(), k);
    }

    ConstIter upperBound(ConstIter pos, const Key& k) const
    {
      while (!kvComp_.keyComp(k, pos->first)) {
        ++pos;
      }
      return pos;
    }

    std::pair< Iter, Iter > equalRange(const Key& k)
    {
      Iter lb = lowerBound(k);
      return std::make_pair(lb, upperBound(lb, k));
    }

    std::pair< ConstIter, ConstIter > equalRange(const Key& k) const
    {
      ConstIter lb = lowerBound(k);
      return std::make_pair(lb, upperBound(lb, k));
    }

    Compare keyComp() const
    {
      return kvComp_.keyComp;
    }

    KVComp kvComp() const
    {
      return kvComp_;
    }

   private:
    ForwardList< kvPair > pairs_;
    KVComp kvComp_;
  };

  template< typename Key, typename Value, typename Compare >
  bool operator==(const Dictionary< Key, Value, Compare >& lhs, const Dictionary< Key, Value, Compare >& rhs)
  {
    typename Dictionary< Key, Value, Compare >::ConstIter lend = lhs.cend();
    typename Dictionary< Key, Value, Compare >::ConstIter rend = rhs.cend();
    typename Dictionary< Key, Value, Compare >::ConstIter liter = lhs.cbegin();
    typename Dictionary< Key, Value, Compare >::ConstIter riter = rhs.cbegin();
    for (; liter != lend && riter != rend; ++liter, ++riter) {
      if (!(*liter == *riter)) {
        return false;
      }
    }
    return liter == lend && riter == rend;
  }

  template< typename Key, typename Value, typename Compare >
  bool operator!=(const Dictionary< Key, Value, Compare >& lhs, const Dictionary< Key, Value, Compare >& rhs)
  {
    return !(lhs == rhs);
  }

  template< typename Key, typename Value, typename Compare, typename UnaryPredicate >
  size_t eraseIf(Dictionary< Key, Value, Compare >& d, UnaryPredicate check)
  {
    size_t count = 0;
    for (typename Dictionary< Key, Value, Compare >::Iter i = d.beforeBegin(); i.nodePtr->next != nullptr;) {
      if (check(i.nodePtr->next->val)) {
        d.eraseAfter(i);
        count++;
      } else {
        ++i;
      }
    }
    return count;
  }
}

#endif
