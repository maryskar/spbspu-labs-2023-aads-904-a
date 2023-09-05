#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdexcept>
#include <iostream>
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
      
      std::pair<Iterator, bool> insert(const Key& key, const Value& value)
      {
        Iterator prev_node_ptr = data.before_begin();
        for (Node& cur_node : data)
        {
          if (cur_node.key == key)
          {
            return std::make_pair(Iterator(&cur_node), false);
          }
          if (Compare(cur_node.key, key))
          {
            break;
          }
          prev_node_ptr = Iterator(&cur_node);
        }
        return std::make_pair(data.insert_after(prev_node_ptr, Node(key, value)), true);
      }

      Iterator find(const Key& key)
      {
        for (Node& cur_node : data_)
        {
          if (cur_node.key == key)
          {
            return Iterator(&cur_node);
          }
        }
        return data_.end();
      }

      ConstIterator find(const Key& key) const
      {
        for (const Node& cur_node : data_)
        {
          if (cur_node.key == key)
          {
            return ConstIterator(&cur_node);
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

      void complement(const Dictionary< Key, Value, Compare >& other)
      {
        Dictionary< Key, Value, Compare > result;
        for (const Node& cur_node : *this)
        {
          if (!other.contains(cur_node))
          {
            result.insert(cur_node.key, cur_node.value);
          }
        }
      }
    private:

      ForwardList< Node > data_;
  };
}

#endif
