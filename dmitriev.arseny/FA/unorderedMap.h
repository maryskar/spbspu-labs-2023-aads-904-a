#ifndef UNORDEREDMAP_H
#define UNORDEREDMAP_H

#include <forwardList.h>
#include "mapNode.h"

namespace dmitriev
{
  template < typename Key, typename Value, typename Compare = std::equal_to< Key >, typename Hash = std::hash< Key > >
  class UnorderedMap
  {
  public:
    using dataPair = std::pair< const Key, Value >;
    using dataType = MapNode< Key, Value >;
    using fList = ForwardList< dataType >;
    using iterator = typename fList::iterator;
    using constIterator = typename fList::constIterator;

    UnorderedMap():
      m_values(),
      m_size(0),
      m_capacity(4),
      m_arr(new iterator[m_capacity]),
      m_cmp(),
      m_hash()
    {}
    UnorderedMap(size_t capacity):
      m_values(),
      m_size(0),
      m_capacity(capacity),
      m_arr(new iterator[m_capacity]),
      m_cmp(),
      m_hash()
    {}
    UnorderedMap(const UnorderedMap& other):
      m_values(),
      m_size(0),
      m_capacity(other.m_capacity),
      m_arr(new iterator[m_capacity]),
      m_cmp(other.m_cmp),
      m_hash(other.m_hash)
    {
      for (constIterator it = other.m_values.constBegin(); it != other.m_values.constEnd(); it++)
      {
        insert({it->key, it->value});
      }
    }
    UnorderedMap(UnorderedMap&& other) noexcept:
      m_values(other.m_values),
      m_size(0),
      m_capacity(other.m_capacity),
      m_arr(other.m_arr),
      m_cmp(other.m_cmp),
      m_hash(other.m_hash)
    {
      other.m_arr = nullptr;
    }
    ~UnorderedMap()
    {
      delete[] m_arr;
    }

    UnorderedMap& operator=(const UnorderedMap& other)
    {
      if (this == std::addressof(other))
      {
        return *this;
      }

      UnorderedMap< Key, Value, Compare, Hash > newMap(other);
      swap(newMap);
      return *this;
    }
    UnorderedMap& operator=(UnorderedMap&& other) noexcept
    {
      if (this == std::addressof(other))
      {
        return *this;
      }

      clear();
      swap(other);
      return *this;
    }



    size_t count(const Key& key) const noexcept
    {
      return isEmpty(find(key));
    }
    iterator find(const Key& key)
    {
      size_t index = m_hash(key) % m_capacity;
      if (isEmpty(m_arr[index]))
      {
        return end();
      }

      iterator result = findInSameIndexes(m_arr[index], index, key);

      if (!isNextIndexCorrect(result, index))
      {
        return end();
      }

      return ++result;
    }
    constIterator find(const Key& key) const
    {
      size_t index = m_hash(key) % m_capacity;
      if (isEmpty(m_arr[index]))
      {
        return constEnd();
      }

      constIterator result = findInSameIndexes(m_arr[index], index, key);

      if (!isNextIndexCorrect(result, index))
      {
        return constEnd();
      }

      return ++result;
    }

    iterator begin() noexcept
    {
      return m_values.begin();
    }
    iterator end() noexcept
    {
      return m_values.end();
    }
    constIterator constBegin() const noexcept
    {
      return m_values.constBegin();
    }
    constIterator constEnd() const noexcept
    {
      return m_values.constEnd();
    }

    void rehash(size_t count)
    {
      if (count < m_capacity * 0.75)
      {
        return;
      }
      UnorderedMap newMap(count);
      for (auto it = begin(); it != end(); it++)
      {
        newMap.insert({it->key, it->value});
      }
      swap(newMap);
    }
    size_t bucketSize(size_t index) const
    {
      if (index >= m_capacity)
      {
        throw std::invalid_argument("incorrect arg");
      }
      iterator it = m_arr[index];
      size_t result = 0;

      while (isNextIndexCorrect(it++, index))
      {
        result++;
      }

      return result;
    }
    size_t bucketCount() const noexcept
    {
      return m_capacity;
    }
    size_t size() const noexcept
    {
      return m_size;
    }
    bool isEmpty() const noexcept
    {
      return m_size == 0;
    }
    bool isEmpty(constIterator it) const noexcept
    {
      return it == constEnd();
    }
    void clear()
    {
      for (size_t i = 0; i < m_size; i++)
      {
        m_arr[i] = end();
      }

      m_values.clear();
      m_size = 0;
    }
    void swap(UnorderedMap& other) noexcept
    {
      m_values.swap(other.m_values);
      std::swap(m_size, other.m_size);
      std::swap(m_capacity, other.m_capacity);
      std::swap(m_arr, other.m_arr);
    }

  private:
    fList m_values;

    size_t m_size;
    size_t m_capacity;
    iterator* m_arr;

    Compare m_cmp;
    Hash m_hash;

    bool isNextIndexCorrect(constIterator it, size_t index) const
    {
      if (isEmpty(it) || isEmpty(std::next(it)))
      {
        return false;
      }

      return std::next(it)->index == index;
    }
    iterator findInSameIndexes(iterator it, size_t index, const Key& key)
    {
      if (isEmpty(it))
      {
        throw std::logic_error("invalid argument");
      }

      for (iterator next = std::next(it); !isEmpty(next); it++, next++)
      {
        bool indexesEqual = next->index == index;
        bool keysEqual = m_cmp(next->key, key);

        if (!indexesEqual || keysEqual)
        {
          return it;
        }
      }

      return it;
    }
    constIterator findInSameIndexes(constIterator it, size_t index, const Key& key) const
    {
      if (isEmpty(it))
      {
        throw std::logic_error("invalid argument");
      }

      for (constIterator next = std::next(it); !isEmpty(next); it++, next++)
      {
        bool indexesEqual = next->index == index;
        bool keysEqual = m_cmp(next->key, key);

        if (!indexesEqual || keysEqual)
        {
          return it;
        }
      }

      return it;
    }

  };
}

#endif
