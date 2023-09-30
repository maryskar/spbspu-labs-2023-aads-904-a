#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdexcept>
#include <utility>
#include "forwardList.h"

namespace potapova
{
  template< typename Key, typename Value, bool (*Compare)(const Key&, const Key&) >
  class Dictionary 
  {
    public:
      struct Node
      {
        Key key;
        Value value;

        Node() noexcept = default;

        Node(const Key& key, const Value& value):
          key(key),
          value(value)
        {

        }

        operator std::pair< Key, Value >()
        {
          return std::make_pair(key, value);
        }
      };

      using Iterator = typename ForwardList< Node >::Iterator;
      using ConstIterator = typename ForwardList< Node >::ConstIterator;

      Iterator begin()
      {
        return data_.begin();
      }

      ConstIterator begin() const
      {
        return data_.begin();
      }

      ConstIterator cbegin() const
      {
        return data_.cbegin();
      }

      Iterator end()
      {
        return data_.end();
      }

      ConstIterator end() const
      {
        return data_.end();
      }

      ConstIterator cend() const
      {
        return data_.cend();
      }
      
      std::pair< Iterator, bool > insert(const Key& key, const Value& value)
      {
        Iterator prev_node_ptr = data_.before_begin();
        for (Iterator cur_node_ptr = data_.begin(); cur_node_ptr != data_.end(); ++cur_node_ptr)
        {
          if (cur_node_ptr->key == key)
          {
            return std::make_pair(cur_node_ptr, false);
          }
          if (Compare(cur_node_ptr->key, key))
          {
            break;
          }
          prev_node_ptr = cur_node_ptr;
        }
        return std::make_pair(data_.insert_after(prev_node_ptr, Node(key, value)), true);
      }

      Iterator find(const Key& key)
      {
        for (Iterator cur_node_ptr = data_.cbegin(); cur_node_ptr != data_.cend(); ++cur_node_ptr)
        {
          if (cur_node_ptr.key == key)
          {
            return cur_node_ptr;
          }
        }
        return data_.end();
      }

      ConstIterator find(const Key& key) const
      {
        for (ConstIterator cur_node_ptr = data_.cbegin(); cur_node_ptr != data_.cend(); ++cur_node_ptr)
        {
          if (cur_node_ptr->key == key)
          {
            return cur_node_ptr;
          }
        }
        return cend();
      }

      Value& at(const Key& key)
      {
        const Iterator result_ptr = find(key);
        if (result_ptr == data_.end())
        {
          throw std::out_of_range("Key was not found in dictionary");
        }
        return *result_ptr;
      }

      const Value& at(const Key& key) const
      {
        const ConstIterator result_ptr = find(key);
        if (result_ptr == data_.end())
        {
          throw std::out_of_range("Key was not found in dictionary");
        }
        return *result_ptr;
      }

      Value& operator[](const Key& key)
      {
        return *insert(key, Value()).first;
      }

      Iterator erase(const Key& key)
      {
        Iterator prev_node_ptr = data.before_begin();
        for (Node& node : data)
        {
          if (node.key == key)
          {
            return data.erase_after(prev_node_ptr);
          }
          prev_node_ptr = Iterator(&node);
        }
      }

      bool contains(const Key& key) const
      {
        return find(key) == cend();
      }

      size_t size() const
      {
        return data_.size();
      }
      
      bool empty() const
      {
        return data_.empty();
      }

      void clear()
      {
        data_.clear();
      }

      Dictionary< Key, Value, Compare > complement(const Dictionary< Key, Value, Compare >& other) const
      {
        Dictionary< Key, Value, Compare > result;
        ConstIterator greater_node_ptr = cbegin();
        ConstIterator less_node_ptr = other.cbegin();
        while (greater_node_ptr != ConstIterator() && less_node_ptr != ConstIterator())
        {
          if (less_node_ptr->key == greater_node_ptr->key)
          {
            ++less_node_ptr;
            ++greater_node_ptr;
            continue;
          }
          else if (Compare(less_node_ptr->key, greater_node_ptr->key))
          {
            std::swap(less_node_ptr, greater_node_ptr);
          }
          result.insert(less_node_ptr->key, less_node_ptr->value);
          ++less_node_ptr;
        }
        ConstIterator extra_node_ptr = greater_node_ptr == ConstIterator() ? less_node_ptr : greater_node_ptr;
        while (extra_node_ptr != ConstIterator())
        {
          result.insert(extra_node_ptr->key, extra_node_ptr->value);
          ++extra_node_ptr;
        }
        return result;
      }

      Dictionary< Key, Value, Compare > intersect(const Dictionary< Key, Value, Compare >& other) const
      {
        Dictionary< Key, Value, Compare > result;
        ConstIterator node_ptr = cbegin();
        ConstIterator other_node_ptr = other.cbegin();
        while (node_ptr != cend() && other_node_ptr != other.cend())
        {
          if (node_ptr->key == other_node_ptr->key)
          {
            result.insert(node_ptr->key, node_ptr->value);
            ++node_ptr;
            ++other_node_ptr;
            continue;
          }
          else if (Compare(node_ptr->key, other_node_ptr->key))
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

      Dictionary< Key, Value, Compare > join(const Dictionary< Key, Value, Compare >& other) const
      {
        Dictionary< Key, Value, Compare > result;
        ConstIterator greater_node_ptr = cbegin();
        ConstIterator less_node_ptr = other.cbegin();
        while (greater_node_ptr != ConstIterator() && less_node_ptr != ConstIterator())
        {
          if (less_node_ptr->key == greater_node_ptr->key)
          {
            result.insert(greater_node_ptr->key, greater_node_ptr->value);
            ++less_node_ptr;
            ++greater_node_ptr;
            continue;
          }
          else if (Compare(less_node_ptr->key, greater_node_ptr->key))
          {
            std::swap(less_node_ptr, greater_node_ptr);
          }
          result.insert(less_node_ptr->key, less_node_ptr->value);
          ++less_node_ptr;
        }
        ConstIterator extra_node_ptr = greater_node_ptr == ConstIterator() ? less_node_ptr : greater_node_ptr;
        while (extra_node_ptr != ConstIterator())
        {
          result.insert(extra_node_ptr->key, extra_node_ptr->value);
          ++extra_node_ptr;
        }
        return result;
      }
    private:
      ForwardList< Node > data_;
  };
}

#endif
