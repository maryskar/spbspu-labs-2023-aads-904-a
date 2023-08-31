#ifndef DICTIONARY_H
#define DICTIONARY_H
#include "ForwardList.h"
namespace timofeev
{
  template< typename Key, typename Value, typename Compare = std::less< Key > >
  class Dictionary
  {
  public:
    using iter = ForwardListIterator< std::pair< Key, Value > >;
    using constIter = ForwardListConstIterator< std::pair< Key, Value > >;
    void push(Key k, Value v);
    Value get(Key k);
    Value drop(Key k);

    Dictionary();
    ~Dictionary() = default;

    //at
    // operator[]
    iter begin() noexcept;
    constIter cbegin() const noexcept;

    iter end() noexcept;
    constIter cend() const noexcept;
    //insert
    //erase
    void swap(Dictionary< Key, Value, Compare >& other);

    size_t count(const Key& key);
    iter find(const Key& key );
    constIter find(const Key& key ) const;
    bool contains(const Key& key) const;

    bool empty() const noexcept;
    size_t size() const noexcept;

    void clear();

  private:
    ForwardList< std::pair< Key, Value > > data_;
    Compare compare_;
    size_t size_;
  };

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare >::Dictionary():
    data_(),
    compare_(),
    size_(0)
  {}

  template< typename Key, typename Value, typename Compare >
  bool  Dictionary< Key, Value, Compare >::empty() const noexcept
  {
    return data_.empty();
  }

  template< typename Key, typename Value, typename Compare >
  size_t Dictionary< Key, Value, Compare >::size() const noexcept
  {
    return size_;
  }

  template< typename Key, typename Value, typename Compare >
  void Dictionary< Key, Value, Compare >::clear()
  {
    data_.clear();
    size_ = 0;
  }

 /* iter begin() noexcept;
  constIter cbegin() const noexcept;
  iter end() noexcept;
  constIter cend() const noexcept;*/
  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare >::iter Dictionary< Key, Value, Compare >::begin() noexcept
  {
    return data_.begin();
  }
  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare >::constIter Dictionary< Key, Value, Compare >::cbegin() const noexcept
  {
    return data_.cbegin();
  }
  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare >::constIter Dictionary< Key, Value, Compare >::cend() const noexcept
  {
    return data_.cend();
  }
  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare >::iter Dictionary< Key, Value, Compare >::end() noexcept
  {
    return data_.end();
  }

  template< typename Key, typename Value, typename Compare >
  void Dictionary< Key, Value, Compare >::swap(Dictionary< Key, Value, Compare >& other)
  {
    data_.swap(other);
    std::swap(size_, other.size_);
    std::swap(compare_, other.compare_);
  }

  /* size_t count(const Key& key);
    iter find(const Key& key );
    constIter find(const Key& key ) const;
    bool contains(const Key& key) const;*/
  template< typename Key, typename Value, typename Compare >
  size_t Dictionary< Key, Value, Compare >::count(const Key& key)
  {
    //чек зис
    size_t couner = 0;
    for(auto i = begin(); i != end(); i++)
    {
      if (auto cur == key)
      {
        couner++;
      }
    }
    return couner;
  }

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare >::iter Dictionary< Key, Value, Compare >::find(const Key& key )
  {

  }

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare >::constIter Dictionary< Key, Value, Compare >::find(const Key& key ) const
  {
    return constIter(find(key));
  }

  template< typename Key, typename Value, typename Compare >
  bool Dictionary< Key, Value, Compare >::contains(const Key& key) const
  {
     
  }


}

#endif //S2_DICTIONARY_H
