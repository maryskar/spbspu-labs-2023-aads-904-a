#ifndef DICTIONARY_H
#define DICTIONARY_H

namespace potapova
{
  template< typename Key, typename Value, typename Compare >
  class Dictionary 
  {
    public:
      void push(const Key& key, const Value& value);
      Value& get(const Key& key);
      const Value& get(const Key& key) const;
      void erase(const Key& key);
      bool contains(const Key& key) const;
      size_t size() const;
      bool empty() const;
      void clear();
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
  };
}

#endif
