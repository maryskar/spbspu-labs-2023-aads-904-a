#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "forwardList.h"

namespace dmitriev
{
  template< typename Key, typename Value, typename Compare = std::less< Key > >
  class Dictionary
  {
  public:
    using fListPair = std::pair< Key, Value >;
    using fList = dmitriev::ForwardList< fListPair >;
    using iterator = typename fList::iterator;
    using constIterator = typename fList::constIterator;

    Dictionary():
      m_fList(),
      m_comp()
    {}
    explicit Dictionary(std::initializer_list< fListPair > initList, const Compare& comp = Compare()):
      m_fList(),
      m_comp(comp)
    {
      insert(initList);
    }

    Dictionary& operator=(std::initializer_list< fListPair > initList)
    {
      m_fList.clear();
      insert(initList);
    }
    Value& operator[](const Key& key)
    {
      iterator it = find(key);
      if (!isEmpty(it))
      {
        return it->second;
      }

      return insert({key, Value()})->second;
    }

    iterator erase(const Key& key)
    {
      iterator it = findBefore(key);
      iterator finded = it;
      finded++;
      if (isEmpty(finded))
      {
        throw std::out_of_range("no reseults with such key");
      }

      return m_fList.eraseAfter(it);
    }

    iterator eraseAfter(constIterator pos)
    {
      return m_fList.eraseAfter(pos);
    }
    iterator eraseAfter(constIterator first, constIterator last)
    {
      return m_fList.eraseAfter(first, last);
    }

    template< typename... Args >
    iterator emplace(Args... args)
    {
      return insert(std::forward< Args >(args)...);
    }

    iterator insert(const fListPair& keyValue)
    {
      if (constBegin() == constEnd())
      {
        return m_fList.insertAfter(constBeforeBegin(), keyValue);
      }

      iterator it = upperBoundBefore(keyValue.first);
      if (isEmpty(it))
      {
        throw std::logic_error("unpredictable behaviour");
      }
      if (it->first == keyValue.first)
      {
        return it;
      }

      return m_fList.insertAfter(it, keyValue);
    }
    iterator insert(fListPair&& keyValue)
    {
      if (constBegin() == constEnd())
      {
        return m_fList.insertAfter(constBeforeBegin(), std::move(keyValue));
      }

      iterator it = upperBoundBefore(keyValue.first);
      if (it->first == keyValue.first)
      {
        return it;
      }

      return m_fList.insertAfter(it, std::move(keyValue));
    }
    template< typename inputIterator >
    void insert(inputIterator first, inputIterator last)
    {
      for (; first != last; first++)
      {
        insert(*first);
      }
    }
    void insert(std::initializer_list< fListPair > initList)
    {
      insert(initList.begin(), initList.end());
    }

    Value& at(const Key& key)
    {
      iterator it = find(key);
      if (isEmpty(it))
      {
        throw std::out_of_range("no reseults with such key");
      }

      return it->second;
    }
    const Value& at(const Key& key) const
    {
      constIterator it = constFind(key);
      if (isEmpty(it))
      {
        throw std::out_of_range("no reseults with such key");
      }

      return it->second;
    }

    iterator lowerBoundBefore(const Key& key)
    {
      iterator result = beforeBegin();

      for (iterator it = begin(); (!isEmpty(it)) && m_comp(it->first, key); result++, it++)
      {
      }

      return result;
    }
    iterator lowerBound(const Key& key)
    {
      return ++lowerBoundBefore(key);
    }

    iterator upperBoundBefore(const Key& key)
    {
      iterator result = beforeBegin();

      for (iterator it = begin(); (!isEmpty(it)) && !m_comp(key, it->first); result++, it++)
      {
      }

      return result;
    }
    iterator upperBound(const Key& key)
    {
      return ++upperBoundBefore(key);
    }

    iterator findBefore(const Key& key)
    {
      iterator result = beforeBegin();

      for (iterator it = begin(); (!isEmpty(it)) && (it->first != key); result++, it++)
      {
      }

      return result;
    }
    iterator find(const Key& key)
    {
      return ++findBefore(key);
    }

    constIterator constFindBefore(const Key& key) const
    {
      constIterator result = constBeforeBegin();

      for (constIterator it = constBegin(); (!isEmpty(it)) && (it->first != key); result++, it++)
      {
      }

      return result;
    }
    constIterator constFind(const Key& key) const
    {
      return ++constFindBefore(key);
    }

    iterator beforeBegin() noexcept
    {
      return m_fList.beforeBegin();
    }
    iterator begin() noexcept
    {
      return m_fList.begin();
    }
    iterator end() noexcept
    {
      return m_fList.end();
    }

    constIterator constBeforeBegin() const noexcept
    {
      return m_fList.constBeforeBegin();
    }
    constIterator constBegin() const noexcept
    {
      return m_fList.constBegin();
    }
    constIterator constEnd() const noexcept
    {
      return m_fList.constEnd();
    }

    bool isEmpty(constIterator it) const noexcept
    {
      return it == constEnd();
    }
    bool isEmpty() const noexcept
    {
      return m_fList.isEmpty();
    }
    void swap(Dictionary& other) noexcept
    {
      m_fList.swap(other.m_fList);
    }
    void clear() noexcept
    {
      m_fList.clear();
    }

  private:
    fList m_fList;
    Compare m_comp;

  };

  template< typename Key, typename Value, typename Compare = std::less< > >
  Dictionary< Key, Value, Compare > complementDictionary(const Dictionary< Key, Value, Compare >& lhs,
    const Dictionary< Key, Value, Compare > rhs)
  {
    Dictionary< Key, Value, Compare > newDic;

    for (typename Dictionary< Key, Value, Compare >::constIterator it = lhs.constBegin(); !newDic.isEmpty(it); it++)
    {
      if (newDic.isEmpty(rhs.constFind(it->first)))
      {
        newDic.insert(*it);
      }
    }
    for (typename Dictionary< Key, Value, Compare >::constIterator it = rhs.constBegin(); !newDic.isEmpty(it); it++)
    {
      if (newDic.isEmpty(lhs.constFind(it->first)))
      {
        newDic.insert(*it);
      }
    }

    return newDic;
  }

  template< typename Key, typename Value, typename Compare = std::less< > >
  Dictionary< Key, Value, Compare > intersectDictionary(const Dictionary< Key, Value, Compare >& lhs,
    const Dictionary< Key, Value, Compare > rhs)
  {
    Dictionary< Key, Value, Compare > newDic;

    for (typename Dictionary< Key, Value, Compare >::constIterator it = lhs.constBegin(); !newDic.isEmpty(it); it++)
    {
      if (!newDic.isEmpty(rhs.constFind(it->first)))
      {
        newDic.insert(*it);
      }
    }

    return newDic;
  }

  template< typename Key, typename Value, typename Compare = std::less< > >
  Dictionary< Key, Value, Compare > unionDictionary(const Dictionary< Key, Value, Compare >& lhs,
    const Dictionary< Key, Value, Compare > rhs)
  {
    Dictionary< Key, Value, Compare > newDic;

    for (typename Dictionary< Key, Value, Compare >::constIterator it = lhs.constBegin(); !newDic.isEmpty(it); it++)
    {
      newDic.insert(*it);
    }
    for (typename Dictionary< Key, Value, Compare >::constIterator it = rhs.constBegin(); !newDic.isEmpty(it); it++)
    {
      if (newDic.isEmpty(lhs.constFind(it->first)))
      {
        newDic.insert(*it);
      }
    }

    return newDic;
  }

}

#endif
