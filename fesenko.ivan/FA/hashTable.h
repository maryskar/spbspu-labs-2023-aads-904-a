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
    template< typename P >
    void insert(P &&);
    void erase(const key_type &);
    void clear() noexcept;
    bool find(const key_type &);
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
      data_[index].collision_list.push_fornt(value);
    }
  }

  template< typename T >
  template< typename P >
  void HashTable< T >::insert(P &&value)
  {
    static_assert(std::is_constructible< value_type, P && >::value, "Can`t construct value type");
    const value_type temp(std::forward< P >(value));
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
      if (!wt.collision_list.empty()) {
        auto pair = wt.collision_list.front();
        wt.collision_list.pop_front();
        wt.word = pair.first;
        wt.data = pair.second;
      } else {
        size_--;
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
        wt.collision_list.push_back(copy.front());
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
}
#endif
