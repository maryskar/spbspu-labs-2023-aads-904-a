#ifndef HASHTABLE_T
#define HASHTABLE_H
#include <vector>
#include <string>
#include "wordType.h"
#include "hash.h"
namespace fesenko
{
  class HashTable
  {
   public:
    using this_t = HashTable;
    using key_type = std::string;
    using mapped_type = WordType;
    using data_t = std::vector< mapped_type >;
    HashTable();
    HashTable(const this_t &) = default;
    HashTable(this_t &&);
    this_t &operator=(const this_t &);
    this_t &operator=(this_t &&);
    ~HashTable() = default;
    bool empty() const noexcept;
    size_t size() const noexcept;
    size_t max_size() const noexcept;
    mapped_type &operator[](const key_type &);
    mapped_type &operator[](key_type &&);
   private:
    size_t size_;
    size_t capacity_;
    data_t data_;
  };

  HashTable::HashTable():
    size_(0),
    capacity_(100),
    data_(data_t(100))
  {}

  HashTable::HashTable(this_t &&other):
    size_(other.size_),
    capacity_(other.capacity_),
    data_(std::move(other.data_))
  {
    other.size_ = 0;
    other.capacity_ = 0;
  }

  HashTable &HashTable::operator=(const this_t &other)
  {
    if (this != std::addressof(other)) {
      data_ = other.data_;
      size_ = other.size_;
      capacity_ = other.capacity_;
    }
    return *this;
  }

  HashTable &HashTable::operator=(this_t &&other)
  {
    if (this != std::addressof(other)) {
      data_ = std::move(other.data_);
      size_ = other.size_;
      capacity_ = other.capacity_;
      other.size_ = 0;
      other.capacity_ = 0;
    }
    return *this;
  }

  bool HashTable::empty() const noexcept
  {
    return size_ == 0;
  }

  size_t HashTable::size() const noexcept
  {
    return size_;
  }

  size_t HashTable::max_size() const noexcept
  {
    return capacity_;
  }

  WordType &HashTable::operator[](const key_type &key)
  {
    uint32_t index = generate_jenkins_hash(key, capacity_);
    return data_[index];
  }

  WordType &HashTable::operator[](key_type &&key)
  {
    return (*this)[key];
  }
}
#endif
