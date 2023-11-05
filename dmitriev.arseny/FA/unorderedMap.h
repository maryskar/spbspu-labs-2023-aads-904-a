#ifndef UNORDEREDMAP_H
#define UNORDEREDMAP_H

#include <forwardList.h>
#include "mapNode.h"

namespace dmitriev
{
  template < class Key, class Value, class Compare = std::equal_to< Key >, class Hash = std::hash< Key > >
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
    explicit UnorderedMap(size_t capacity):
      m_values(),
      m_size(0),
      m_capacity(capacity),
      m_arr(new iterator[m_capacity]),
      m_cmp(),
      m_hash()
    {}
    UnorderedMap(std::initializer_list< dataPair > iList):
      UnorderedMap()
    {
      insert(iList);
    }
    UnorderedMap(const UnorderedMap& other):
      m_values(),
      m_size(0),
      m_capacity(other.m_capacity),
      m_arr(new iterator[m_capacity]),
      m_cmp(other.m_cmp),
      m_hash(other.m_hash)
    {
      for (constIterator it = other.constBegin(); it != other.constEnd(); it++)
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

      UnorderedMap newMap(other);
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

    Value& operator[](const Key& key)
    {
      iterator it = find(key);
      if (!isEmpty(it))
      {
        return it->value;
      }

      return insert({key, Value()})->value;
    }

    Value& at(const Key& key)
    {
      iterator it = find(key);
      if (isEmpty(it))
      {
        throw std::out_of_range("no results with such key");
      }

      return it->value;
    }
    const Value& at(const Key& key) const
    {
      constIterator it = find(key);
      if (isEmpty(it))
      {
        throw std::out_of_range("no results with such key");
      }

      return it->value;
    }

    iterator erase(const Key& key)
    {
      size_t index = m_hash(key) % m_capacity;
      if (isEmpty(m_arr[index]))
      {
        return end();
      }

      iterator it = findInSameIndexes(m_arr[index], index, key);
      iterator sought = std::next(it);

      if (!isNextKeyCorrect(it, key))
      {
        return end();
      }

      if (!(isEmpty(std::next(sought)) || isNextIndexCorrect(sought, index)))
      {
        size_t prIndex = std::next(sought)->index;
        m_arr[prIndex] = it;
      }

      iterator result = m_values.eraseAfter(it);

      if (!isNextIndexCorrect(m_arr[index], index))
      {
        m_arr[index] = end();
      }

      return result;
    }

    iterator insert(const dataPair& keyValue)
    {
      if (m_size >= m_capacity * 0.75)
      {
        rehash(m_capacity * 2);
      }

      size_t index = m_hash(keyValue.first) % m_capacity;
      dataType data{index, keyValue.first, keyValue.second};

      if (isEmpty())
      {
        m_arr[index] = m_values.beforeBegin();

        m_size++;
        return m_values.insertAfter(m_arr[index], data);
      }

      if (isEmpty(m_arr[index]))
      {
        size_t prIndex = m_values.begin()->index;
        m_arr[prIndex] = m_values.insertAfter(m_values.beforeBegin(), data);
        m_arr[index] = m_values.beforeBegin();

        m_size++;
        return m_arr[prIndex];
      }

      iterator it = findInSameIndexes(m_arr[index], data.index, data.key);
      if (isNextKeyCorrect(it, data.key))
      {
        return std::next(it);
      }

      return m_values.insertAfter(m_arr[index], data);
    }
    iterator insert(dataPair&& keyValue)
    {
      if (m_size >= m_capacity * 0.75)
      {
        rehash(m_capacity * 2);
      }

      size_t index = m_hash(keyValue.first) % m_capacity;
      dataType data{index, std::move(keyValue.first), std::move(keyValue.second)};

      if (isEmpty())
      {
        m_arr[index] = m_values.beforeBegin();

        m_size++;
        return m_values.insertAfter(m_arr[index], std::move(data));
      }

      if (isEmpty(m_arr[index]))
      {
        size_t prIndex = m_values.begin()->index;
        m_arr[prIndex] = m_values.insertAfter(m_values.beforeBegin(), std::move(data));
        m_arr[index] = m_values.beforeBegin();

        m_size++;
        return m_arr[prIndex];
      }

      iterator it = findInSameIndexes(m_arr[index], data.index, data.key);
      if (isNextKeyCorrect(it, data.key))
      {
        return std::next(it);
      }

      return m_values.insertAfter(m_arr[index], std::move(data));
    }
    template< typename Iterator >
    void insert(Iterator first, Iterator last)
    {
      while (first != last)
      {
        insert(*first++);
      }
    }
    void insert(std::initializer_list< dataPair > iList)
    {
      insert(iList.begin(), iList.end());
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

    bool isNextKeyCorrect(constIterator it, const Key& key) const
    {
      if (isEmpty(it) || isEmpty(std::next(it)))
      {
        return false;
      }

      return m_cmp(std::next(it)->key, key);
    }
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
