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
    typedef typename std::vector< word_type >::iterator iterator;
    typedef typename std::vector< word_type >::const_iterator const_iterator;
    HashTable();
    HashTable(const this_t &) = default;
    HashTable(this_t &&);
    this_t &operator=(const this_t &);
    this_t &operator=(this_t &&);
    ~HashTable() = default;
    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;
    bool empty() const noexcept;
    size_t size() const noexcept;
    size_t max_size() const noexcept;
    word_type &operator[](const key_type &);
    word_type &operator[](key_type &&);
    word_type &at(const key_type &);
    const word_type &at(const key_type &) const;
    void insert(const value_type &);
    void insert(value_type &&);
    void insert(const key_type &);
    void insert(key_type &&);
    void erase(const key_type &);
    void clear() noexcept;
    bool find(const key_type &);
    bool find(const key_type &) const;
   private:
    size_t size_;
    size_t capacity_;
    data_t data_;
    bool shouldResize() const;
    void resize(size_t newCapacity);
  };

  template< typename T >
  HashTable< T >::HashTable():
    size_(0),
    capacity_(20),
    data_(data_t(20))
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
  typename HashTable< T >::iterator HashTable< T >::begin() noexcept
  {
    return data_.begin();
  }

  template< typename T >
  typename HashTable< T >::const_iterator HashTable< T >::begin() const noexcept
  {
    return data_.cbegin();
  }

  template< typename T >
  typename HashTable< T >::const_iterator HashTable< T >::cbegin() const noexcept
  {
    return data_.cbegin();
  }

  template< typename T >
  typename HashTable< T >::iterator HashTable< T >::end() noexcept
  {
    return data_.end();
  }

  template< typename T >
  typename HashTable< T >::const_iterator HashTable< T >::end() const noexcept
  {
    return data_.cend();
  }

  template< typename T >
  typename HashTable< T >::const_iterator HashTable< T >::cend() const noexcept
  {
    return data_.cend();
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
      data_[index].word = value.first;
      data_[index].data = value.second;
      size_++;
    } else {
      data_[index].collision_list.push_front(value);
    }
    if (shouldResize()) {
      resize(capacity_ * 2);
    }
  }

  template< typename T >
  void HashTable< T >::insert(value_type &&value)
  {
    const value_type temp(value);
    insert(temp);
  }

  template< typename T >
  void HashTable< T >::insert(const key_type &key)
  {
    uint32_t index = generate_jenkins_hash(key, capacity_);
    if (data_[index].word.empty()) {
      data_[index].word = key;
      size_++;
    } else if (data_[index].word != key) {
      T temp;
      data_[index].collision_list.push_front(std::make_pair(key, temp));
    }
    if (shouldResize()) {
      resize(capacity_ * 2);
    }
  }

  template< typename T >
  void HashTable< T >::insert(key_type &&key)
  {
    const key_type temp(key);
    insert(temp);
  }

  template< typename T >
  void HashTable< T >::erase(const key_type &key)
  {
    uint32_t index = generate_jenkins_hash(key, capacity_);
    word_type &wt = data_[index];
    if (key.compare(wt.word) == 0) {
      wt.word = "";
      wt.data.clear();
      if (wt.collision_list.empty()) {
        size_--;
      } else {
        auto pair = wt.collision_list.front();
        wt.collision_list.pop_front();
        wt.word = pair.first;
        wt.data = pair.second;
      }
    } else if (!wt.collision_list.empty()) {
      auto copy = wt.collision_list;
      while (!wt.collision_list.empty()) {
        if (key.compare(wt.collision_list.front().first) == 0) {
          wt.collision_list.pop_front();
          break;
        } else {
          copy.push_front(wt.collision_list.front());
          wt.collision_list.pop_front();
        }
      }
      while (!copy.empty()) {
        wt.collision_list.push_front(copy.front());
        copy.pop_front();
      }
    }
  }

  template< typename T >
  void HashTable< T >::clear() noexcept
  {
    for (auto &it: data_) {
      if (!it.word.empty()) {
        it.word = "";
        it.data.clear();
        it.collision_list.clear();
      }
    }
  }

  template< typename T >
  bool HashTable< T >::find(const key_type &key)
  {
    uint32_t index = generate_jenkins_hash(key, capacity_);
    return !data_[index].word.empty();
  }

  template< typename T >
  bool HashTable< T >::find(const key_type &key) const
  {
    uint32_t index = generate_jenkins_hash(key, capacity_);
    return !data_[index].word.empty();
  }

  template< typename T >
  bool HashTable< T >::shouldResize() const
  {
    double loadFactor = double(size_) / capacity_;
    return loadFactor > 0.7;
  }

  template< typename T >
  void HashTable< T >::resize(size_t newCapacity)
  {
    data_t newData(newCapacity);
    for (auto &it: data_) {
      if (!it.word.empty()) {
        uint32_t newIndex = generate_jenkins_hash(it.word, newCapacity);
        newData[newIndex].word = it.word;
        newData[newIndex].data = it.data;
        while (!it.collision_list.empty()) {
          auto pair = it.collision_list.front();
          it.collision_list.pop_front();
          newIndex = generate_jenkins_hash(pair.first, newCapacity);
          newData[newIndex].word = pair.first;
          newData[newIndex].data = pair.second;
        }
      }
    }
    data_ = std::move(newData);
    capacity_ = newCapacity;
  }
}
#endif
