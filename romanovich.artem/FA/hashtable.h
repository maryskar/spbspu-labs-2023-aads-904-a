#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <cstddef>
#include <vector>
#include "wordentry.h"
namespace romanovich
{
  class HashTable
  {
  public:
    using data_t = std::vector< WordEntry >;
    HashTable();
    HashTable(const HashTable &other) = default;
    HashTable(HashTable &&other) noexcept;
    HashTable &operator=(const HashTable &other);
    HashTable &operator=(HashTable &&other) noexcept;
    explicit HashTable(size_t size, size_t capacity = 100);
    size_t getSize() const;
    size_t getCapacity() const;
    const data_t &getData() const;
    WordEntry &operator[](const std::string &key);
    void addKey(const std::string &key);
    void removeKey(const std::string &key);
    void addValue(const std::string &key, const std::string &trans);
    void removeValue(const std::string &key, const std::string &trans);
    std::ostream &print(std::ostream &out) const;
    void resize(size_t newCapacity);
    void addWordsFromAnother(const romanovich::HashTable &table);
    void addLevelWordsFromAnother(const romanovich::HashTable &table);
  private:
    size_t size_;
    size_t capacity_;
    data_t data_;
    bool shouldResize() const;
  };
}
#endif
