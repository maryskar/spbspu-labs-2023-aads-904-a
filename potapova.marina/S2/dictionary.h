#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <utility>
#include <stdexcept>
#include "forwardList.h"

namespace potapova
{
  template< typename Key, typename Value, typename Comparator = std::less< Key > >
  class Dictionary 
  {
    public:
      using Iterator = typename ForwardList< std::pair< const Key, Value > >::Iterator;
      using ConstIterator = typename ForwardList< std::pair< const Key, Value > >::ConstIterator;

      Iterator begin() noexcept
      {
        return data.begin();
      }

      ConstIterator begin() const noexcept
      {
        return data.begin();
      }

      ConstIterator cbegin() const noexcept
      {
        return data.cbegin();
      }

      Iterator end() noexcept
      {
        return data.end();
      }

      ConstIterator end() const noexcept
      {
        return data.end();
      }

      ConstIterator cend() const noexcept
      {
        return data.cend();
      }

      std::pair<Iterator, bool> insert(const Key& key, const Value& value)
      {
        Iterator prev_node_ptr = data.before_begin();
        for (Iterator cur_node_ptr = data.begin(); cur_node_ptr != data.end(); ++cur_node_ptr)
        {
          if (!comparator(cur_node_ptr->first, key) && !comparator(key, cur_node_ptr->first))
          {
            return std::make_pair(cur_node_ptr, false);
          }
          if (comparator(key, cur_node_ptr->first))
          {
            break;
          }
          prev_node_ptr = cur_node_ptr;
        }
        return std::make_pair(data.insert_after(prev_node_ptr, std::make_pair(key, value)), true);
      }

      Iterator find(const Key& key) noexcept
      {
        for (Iterator cur_node_ptr = data.begin(); cur_node_ptr != data.end(); ++cur_node_ptr)
        {
          if (!comparator(cur_node_ptr->first, key) && !comparator(key, cur_node_ptr->first))
          {
            return cur_node_ptr;
          }
        }
        return data.end();
      }

      ConstIterator find(const Key& key) const noexcept
      {
        for (ConstIterator cur_node_ptr = data.cbegin(); cur_node_ptr != data.cend(); ++cur_node_ptr)
        {
          if (!comparator(cur_node_ptr->first, key) && !comparator(key, cur_node_ptr->first))
          {
            return cur_node_ptr;
          }
        }
        return cend();
      }

      Value& at(const Key& key)
      {
        const Iterator result_ptr = find(key);
        if (result_ptr == data.end())
        {
          throw std::out_of_range("Key was not found in dictionary");
        }
        return result_ptr->value;
      }

      const Value& at(const Key& key) const
      {
        const ConstIterator result_ptr = find(key);
        if (result_ptr == data.cend())
        {
          throw std::out_of_range("Key was not found in dictionary");
        }
        return result_ptr->value;
      }

      Value& operator[](const Key& key)
      {
        return insert(key, Value()).first->second;
      }

      Iterator erase(const Key& key) noexcept
      {
        Iterator prev_node_ptr = data.before_begin();
        for (Iterator cur_node_ptr = data.begin(); cur_node_ptr != data.end(); ++cur_node_ptr)
        {
          if (!comparator(cur_node_ptr->key, key) && !comparator(key, cur_node_ptr->key))
          {
            return data.erase_after(prev_node_ptr);
          }
          prev_node_ptr = cur_node_ptr;
        }
      }

      bool contains(const Key& key) const noexcept
      {
        return find(key) == cend();
      }

      size_t size() const noexcept
      {
        return data.size();
      }
      
      bool empty() const noexcept
      {
        return data.empty();
      }

      void clear() noexcept
      {
        data.clear();
      }

      Dictionary< Key, Value, Comparator > complement(const Dictionary< Key, Value, Comparator >& other) const
      {
        Dictionary< Key, Value, Comparator > result;
        ConstIterator greater_node_ptr = cbegin();
        ConstIterator less_node_ptr = other.cbegin();
        while (greater_node_ptr != ConstIterator() && less_node_ptr != ConstIterator())
        {
          if (!comparator(less_node_ptr->first, greater_node_ptr->first) &&
            !comparator(greater_node_ptr->first, less_node_ptr->first))
          {
            ++less_node_ptr;
            ++greater_node_ptr;
            continue;
          }
          else if (comparator(greater_node_ptr->first, less_node_ptr->first))
          {
            std::swap(less_node_ptr, greater_node_ptr);
          }
          result.insert(less_node_ptr->first, less_node_ptr->second);
          ++less_node_ptr;
        }
        ConstIterator extra_node_ptr = greater_node_ptr == ConstIterator() ? less_node_ptr: greater_node_ptr;
        while (extra_node_ptr != ConstIterator())
        {
          result.insert(extra_node_ptr->first, extra_node_ptr->second);
          ++extra_node_ptr;
        }
        return result;
      }

      Dictionary< Key, Value, Comparator > intersect(const Dictionary< Key, Value, Comparator >& other) const
      {
        Dictionary< Key, Value, Comparator > result;
        ConstIterator node_ptr = cbegin();
        ConstIterator other_node_ptr = other.cbegin();
        while (node_ptr != cend() && other_node_ptr != other.cend())
        {
          if (!comparator(node_ptr->first, other_node_ptr->first) &&
            !comparator(other_node_ptr->first, node_ptr->first))
          {
            result.insert(node_ptr->first, node_ptr->second);
            ++node_ptr;
            ++other_node_ptr;
            continue;
          }
          else if (comparator(other_node_ptr->first, node_ptr->first))
          {
            ++other_node_ptr;
          }
          else
          {
            ++node_ptr;
          }
        }
        return result;
      }

      Dictionary< Key, Value, Comparator > join(const Dictionary< Key, Value, Comparator >& other) const
      {
        Dictionary< Key, Value, Comparator > result;
        ConstIterator greater_node_ptr = cbegin();
        ConstIterator less_node_ptr = other.cbegin();
        while (greater_node_ptr != ConstIterator() && less_node_ptr != ConstIterator())
        {
          if (comparator(greater_node_ptr->first, less_node_ptr->first))
          {
            std::swap(less_node_ptr, greater_node_ptr);
          }
          result.insert(less_node_ptr->first, less_node_ptr->second);
          ++less_node_ptr;
        }
        ConstIterator extra_node_ptr = greater_node_ptr == ConstIterator() ? less_node_ptr: greater_node_ptr;
        while (extra_node_ptr != ConstIterator())
        {
          result.insert(extra_node_ptr->first, extra_node_ptr->second);
          ++extra_node_ptr;
        }
        return result;
      }
    private:
      ForwardList< std::pair< const Key, Value > > data;
      Comparator comparator;
  };
}

#endif
