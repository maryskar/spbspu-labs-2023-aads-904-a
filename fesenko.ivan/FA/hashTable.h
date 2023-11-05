#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <vector>
#include <string>
#include "wordType.h"
#include "hash.h"
namespace fesenko
{
  template< typename T >
  class HashTable
  {
   public:
    using this_t = HashTable;
    using key_type = std::string;
    using mapped_type = T;
    using value_type = std::pair< key_type, mapped_type >;
    using word_type = WordType< T >;
    using data_t = std::vector< word_type >;
    HashTable();
    HashTable(const this_t &) = default;
    HashTable(this_t &&);
    this_t &operator=(const this_t &);
    this_t &operator=(this_t &&);
    ~HashTable() = default;
    bool empty() const noexcept;
    size_t size() const noexcept;
    size_t max_size() const noexcept;
    word_type &operator[](const key_type &);
    word_type &operator[](key_type &&);
    word_type &at(const key_type &);
    const word_type &at(const key_type &) const;
    void insert(const value_type &);
   private:
    size_t size_;
    size_t capacity_;
    data_t data_;
  };

  template< typename T >
  HashTable< T >::HashTable():
    size_(0),
    capacity_(100),
    data_(data_t(100))
  {}

  template< typename T >
  HashTable< T >::HashTable(this_t &&other):
    size_(other.size_),
    capacity_(other.capacity_),
    data_(std::move(other.data_))
  {
    other.size_ = 0;
    other.capacity_ = 0;
  }

  template< typename T >
  HashTable< T > &HashTable< T >::operator=(const this_t &other)
  {
    if (this != std::addressof(other)) {
      data_ = other.data_;
      size_ = other.size_;
      capacity_ = other.capacity_;
    }
    return *this;
  }

  template< typename T >
  HashTable< T > &HashTable< T >::operator=(this_t &&other)
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

  template< typename T >
  bool HashTable< T >::empty() const noexcept
  {
    return size_ == 0;
  }

  template< typename T >
  size_t HashTable< T >::size() const noexcept
  {
    return size_;
  }

  template< typename T >
  size_t HashTable< T >::max_size() const noexcept
  {
    return capacity_;
  }

  template< typename T >
  WordType< T > &HashTable< T >::operator[](const key_type &key)
  {
    uint32_t index = generate_jenkins_hash(key, capacity_);
    return data_[index];
  }

  template< typename T >
  WordType< T > &HashTable< T >::operator[](key_type &&key)
  {
    return (*this)[key];
  }

  template< typename T >
  const WordType< T > &HashTable< T >::at(const key_type &key) const
  {
    uint32_t index = generate_jenkins_hash(key, capacity_);
    return data_.at(index);
  }

  template< typename T >
  WordType< T > &HashTable< T >::at(const key_type &key)
  {
    return const_cast< WordType< T > & >((static_cast< const this_t & >(*this)).at(key));
  }

  template< typename T >
  void HashTable< T >::insert(const value_type &value)
  {
    uint32_t index = generate_jenkins_hash(value.first, capacity_);
    if (data_[index].word.empty()) {
      data_[index] = value.second;
      size_++;
    } else {
      data_[index].collision_list.push_fornt(value);
    }
  }
}
#endif
