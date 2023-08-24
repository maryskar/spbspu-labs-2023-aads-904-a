#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdexcept>
#include "forwardList.h"

namespace potapova
{
  template< typename Key, typename Value, bool (*Compare)(const Key&, const Key&) >
  class Dictionary 
  {
    public:
      using Iterator = ForwardList::Iterator;
      using ConstIterator = ForwardList::ConstIterator;

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
      
      void insert(const Key& key, const Value& value)
      {
        Iterator prev_node_ptr = data_.before_begin();
        for (Node& cur_node : data_)
        {
          if (cur_node->key == key)
          {
            cur_node->value = value;
            return;
          }
          if (Compare(cur_node->key, key))
          {
            data_.insert_after(prev_node_ptr, Node(key, value));
            return;
          }
          prev_node_ptr = Iterator(&cur_node);
        }
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

      void erase(const Key& key)
      {
        Iterator prev_node_ptr = data_.before_begin();
        for (Node& node : data_)
        {
          if (node.key == key)
          {
            data_.erase_after(prev_node_ptr);
            return;
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
    private:
      struct Node
      {
        Key key;
        Value value;

        Node(const Key& key, const Value& value):
          key(key),
          value(value)
        {

        }
      };

      ForwardList< Node > data_;
  };
}

#endif
