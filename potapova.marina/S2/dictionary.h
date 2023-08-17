#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdexcept>
#include "forwardList.h"

namespace potapova
{
  template< typename Key, typename Value, typename Compare >
  class Dictionary 
  {
    public:
      void push(const Key& key, const Value& value)
      {
        Node new_node(key, value);
        data.push_front(new_node);
      }

      Value& find(const Key& key)
      {
        for (Node& node : data)
        {
          if (node.key == key)
          {
            return node.value;
          }
        }
        throw std::out_of_range("Key was not found in dictionary");
      }

      const Value& find(const Key& key) const
      {
        for (const Node& node : data)
        {
          if (node.key == key)
          {
            return node.value;
          }
        }
        throw std::out_of_range("Key was not found in dictionary");
      }

      void erase(const Key& key)
      {
        auto it = data.begin();
        while (it != data.end())
        {
          if (it->key == key)
          {
            it = data.erase(it);
          }
          else
          {
            ++it;
          }
        }
      }

      bool contains(const Key& key) const
      {
        auto it = data.begin();
        while (it != data.end())
        {
          if (it->key == key)
          {
            return true;
          }
          ++it;
        }
        return false;
      }

      size_t size() const
      {
        return data.size();
      }
      
      bool empty() const
      {
        return data.empty();
      }

      void clear()
      {
        return data.clear();
      }
      
      void print(const std::string& dataset) const;
      void complement(const std::string& new_dataset, const std::string& dataset1, const std::string& dataset2);
      void intersect(const std::string& new_dataset, const std::string& dataset1, const std::string& dataset2);
      void join(const std::string& new_dataset, const std::string& dataset1, const std::string& dataset2);
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

      class CompareWrapper
      {
        public:
          CompareWrapper(const Compare& c):
            comp(c)
          {

          }
          bool operator()(const Node& lhs, const Node& rhs) const
          {
            return comp(lhs.key, rhs.key);
          }
        private:
          Compare comp;
      };

      ForwardList< Node > data;
      CompareWrapper compare;
  };
}

#endif
