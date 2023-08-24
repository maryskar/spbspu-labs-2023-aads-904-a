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

      Value& find(const Key& key)
      {
        for (Node& node : data_)
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
        for (const Node& node : data_)
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
        auto it = data_.begin();
        while (it != data_.end())
        {
          if (it->key == key)
          {
            it = data_.erase(it);
          }
          else
          {
            ++it;
          }
        }
      }

      bool contains(const Key& key) const
      {
        auto it = data_.begin();
        while (it != data_.end())
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
        return data_.size();
      }
      
      bool empty() const
      {
        return data_.empty();
      }

      void clear()
      {
        return data_.clear();
      }
      
      void print(const std::string& dataset) const
      {
        if (data_.empty())
        {
          std::cout << "<EMPTY>" << '\n';
          return;
        }
        auto it = data_.lower_bound(dataset);
        if (it == data_.end() && it->key == dataset)
        {
          std::cout << it->key << " " << it->value << " ";
          ++it;
        }
        std::cout << '\n';
      }

      void complement(const std::string& new_dataset, const std::string& dataset1, const std::string& dataset2)
      {
        Dictionary< Key, Value, Compare > result;
        Dictionary< Key, Value, Compare >* ptr_dataset1 = getDictionaryPointer(dataset1);
        Dictionary< Key, Value, Compare >* ptr_dataset2 = getDictionaryPointer(dataset2);
        if (ptr_dataset1 == nullptr || ptr_dataset2 == nullptr)
        {
          throw std::runtime_error("One or both datasets not found");
        }
        for (auto it = ptr_dataset1->data_.begin(); it != ptr_dataset1->data_.end(); ++it)
        {
          const Key& key = it->key;
          const Value& value = it->value;
          if (!ptr_dataset1->find(key))
          {
            result.push(key, value);
          }
        }
        dictionaries[new_dataset] = result;
      }

      Dictionary< Key, Value, Compare >* getDictionaryPointer(const std::string& dataset)
      {
        auto iter = dictionaries.find(dataset);
        if (iter != dictionaries.end())
        {
          return &(iter->second);
        }
        return nullptr;
      }

      void intersect(const std::string& new_dataset, const std::string& dataset1, const std::string& dataset2)
      {
        if (!dictionaries.count(dataset1) || !dictionaries.count(dataset2))
        {
          throw std::runtime_error("Not found input dictionaries");
        }
        const std::unordered_map< Key, Value >& dictionary1 = dictionaries[dataset1];
        const std::unordered_map< Key, Value >& dictionary2 = dictionaries[dataset2];
        std::unordered_map< Key, Value > intersection;
        for (const auto& pair1 : dictionary1)
        {
          const Key& key = pair1.first;
          if (dictionary2.count(key))
          {
            if (pair1.first != pair2.first)
            {
              intersection[key] = pair1.second;
            }
          }
        }
        dictionaries[new_dataset] = intersection;
      }
      
      void join(const std::string& new_dataset, const std::string& dataset1, const std::string& dataset2)
      {
        if (!dictionaries.count(dataset1) || !dictionaries.count(dataset2))
        {
          throw std::runtime_error("Not found input dictionaries");
        }
        const std::unordered_map< Key, Value >& dictionary1 = dictionaries[dataset1];
        const std::unordered_map< Key, Value >& dictionary2 = dictionaries[dataset2];
        std::unordered_map< Key, Value > new_dictionary;
        for (const auto& pair1 : dictionary1)
        {
          new_dictionary[pair1.first] = pair1.second;
        }
        for (const auto& pair2 : dictionary2)
        {
          if (pair1.first != pair2.first)
          {
            new_dictionary[pair2.first] = pair2.second;
          }
        }
        dictionaries[new_dataset] = new_dictionary;
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

      class CompareWrapper
      {
        public:
          CompareWrapper(const Compare& c):
            comp_(c)
          {

          }
          bool operator()(const Node& lhs, const Node& rhs) const
          {
            return comp_(lhs.key, rhs.key);
          }
        private:
          Compare comp_;
      };

      ForwardList< Node > data_;
      CompareWrapper compare_;
      std::unordered_map< std::string, std::string > dictionaries;
  };
}

#endif
