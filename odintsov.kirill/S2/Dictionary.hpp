#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <functional>
#include <initializer_list>
#include <utility>

#include "ForwardIterator.hpp"
#include "ForwardList.hpp"

namespace odintsov {
  template< typename Key, typename Value, typename Compare = std::less< Key > >
  class Dictionary {
   public:
    using kvPair = std::pair< const Key, Value >;
    using Iter = detail::ForwardIterator< kvPair >;
    using ConstIter = detail::ConstForwardIterator< kvPair >;
    using ListNode = typename ForwardList< kvPair >::Node;

    Dictionary();
    Dictionary(const Dictionary& d);
    Dictionary(Dictionary&& d);
    explicit Dictionary(std::initializer_list< kvPair > il, const Compare& comp = Compare());
    explicit Dictionary(const Compare& comp);
    ~Dictionary();

    Dictionary& operator=(const Dictionary& d);
    Dictionary& operator=(Dictionary&& d);
    Dictionary& operator=(std::initializer_list< kvPair > il);

    Value& at(const Key& k);
    const Value& at(const Key& k) const;
    Value& operator[](const Key& k);
    Value& operator[](Key&& k);

    Iter begin();
    ConstIter cbegin() const;
    Iter end();
    ConstIter cend() const;

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
      return insert(cbegin(), std::make_pair(k, Value(std::forward(val))));
    }

    template< typename V >
    std::pair< Iter, bool > insert(Key&& k, V&& val)
    {
      return insert(cbegin(), std::make_pair(std::move(k), Value(std::forward(val))));
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
      return insert(pos, std::make_pair(k, Value(std::forward(val))));
    }

    template< typename V >
    std::pair< Iter, bool > insert(ConstIter pos, Key&& k, V&& val)
    {
      return insert(pos, std::make_pair(std::move(k), Value(std::forward(val))));
    }

    std::pair< Iter, bool > insert(ConstIter pos, const kvPair& kv)
    {
      Iter lb = lowerBound(pos, kv.first);
      bool insert = lb->first != kv.first;
      if (insert) {
        lb = pairs_.unsafeInsertAfter(lb, kv);
      }
      return std::make_pair(lb, insert);
    }

    std::pair< Iter, bool > insert(ConstIter pos, kvPair&& kv)
    {
      Iter lb = lowerBound(pos, kv.first);
      bool insert = lb->first != kv.first;
      if (insert) {
        lb = pairs_.unsafeInsertAfter(lb, std::move(kv));
      }
      return std::make_pair(lb, insert);
    }
    template< class InputIter >
    void insert(InputIter first, InputIter second);
    void insert(std::initializer_list< kvPair > il);

    template< typename V >
    std::pair< Iter, bool > insertOrAssign(const Key& k, V&& val);
    template< typename V >
    std::pair< Iter, bool > insertOrAssign(Key&& k, V&& val);
    std::pair< Iter, bool > insertOrAssign(const kvPair& kv);
    std::pair< Iter, bool > insertOrAssign(kvPair&& kv);
    template< typename V >
    std::pair< Iter, bool > insertOrAssign(ConstIter pos, const Key& k, V&& v);
    template< typename V >
    std::pair< Iter, bool > insertOrAssign(ConstIter pos, Key&& k, V&& v);
    std::pair< Iter, bool > insertOrAssign(ConstIter pos, const kvPair& kv);
    std::pair< Iter, bool > insertOrAssign(ConstIter pos, kvPair&& kv);

    template< typename... Args >
    std::pair< Iter, bool > emplace(Args&&... args);
    template< typename... Args >
    std::pair< Iter, bool > emplace(ConstIter pos, Args&&... args);
    template< typename... Args >
    std::pair< Iter, bool > tryEmplace(const Key& k, Args&&... args);
    template< typename... Args >
    std::pair< Iter, bool > tryEmplace(Key&& k, Args&&... args);
    template< typename... Args >
    std::pair< Iter, bool > tryEmplace(ConstIter pos, const Key& k, Args&&... args);
    template< typename... Args >
    std::pair< Iter, bool > tryEmplace(ConstIter pos, Key&& k, Args&&... args);

    Iter erase(Iter pos);
    Iter erase(ConstIter pos);
    Iter erase(ConstIter first, ConstIter last);
    bool erase(const Key& k);

    void swap(Dictionary& d);
    template< typename C >
    void merge(Dictionary< Key, Value, C >& src);
    template< typename C >
    void merge(Dictionary< Key, Value, C >&& src);

    Iter find(const Key& k);
    ConstIter find(const Key& k) const;
    bool contains(const Key& k) const;

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
      while (keyComp(pos->first, k)) {
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
      while (!keyComp(k, pos->first)) {
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

   private:
    ForwardList< kvPair > pairs_;
    Compare keyComp;
  };

  template< typename Key, typename Value, typename Compare >
  bool operator==(const Dictionary< Key, Value, Compare >& lhs, const Dictionary< Key, Value, Compare >& rhs);
  template< typename Key, typename Value, typename Compare >
  bool operator!=(const Dictionary< Key, Value, Compare >& lhs, const Dictionary< Key, Value, Compare >& rhs);

  template< typename Key, typename Value, typename Compare, typename UnaryPredicate >
  size_t eraseIf(Dictionary< Key, Value, Compare >& d, UnaryPredicate check);
}

#endif
