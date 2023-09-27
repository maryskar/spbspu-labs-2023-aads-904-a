#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <functional>
#include "ForwardList.h"
namespace aksenov
{
  template< typename Key, typename T, typename Compare = std::less< Key > >
  class Dictionary
  {
  public:
    using keyType = Key;
    using mappedType = T;
    using valueType = std::pair< const Key, T >;
    using sizeType = std::size_t;
    using difference_type = std::ptrdiff_t;
    using keyCompare = Compare;
    using reference = valueType &;
    using constReference = const valueType &;
    using pointer = valueType *;
    using constPointer = const valueType *;
    using iterator = typename ForwardList< valueType >::iterator;
    using constIterator = typename ForwardList< valueType >::constIterator;
    using thisT = Dictionary< Key, T, Compare >;

    Dictionary();
    Dictionary(const Dictionary< Key, T, Compare > &other);
    Dictionary(Dictionary< Key, T, Compare > &&other);
    ~Dictionary() = default;

    thisT &operator=(const thisT &other);
    thisT &operator=(thisT &&other);
    mappedType &operator[](const Key &key);
    mappedType &operator[](Key &&key);

    iterator begin() noexcept;
    constIterator begin() const noexcept;
    constIterator cbegin() const noexcept;
    iterator end() noexcept;
    constIterator end() const noexcept;
    constIterator cend() const noexcept;
    iterator find(const Key &key);
    constIterator find(const Key &key) const;
    iterator eraseAfter(constIterator pos);
    iterator eraseAfter(constIterator first, constIterator last);

    mappedType &at(const Key &key);
    const mappedType &at(const Key &key) const;
    bool isEmpty() const noexcept;
    sizeType size() const noexcept;
    void clear();
    void swap(thisT &other);
    sizeType count(const keyType &key) const;
    bool contains(const Key &key) const;
    std::pair< iterator, bool > insert(const valueType &value);
    template< typename P >
    std::pair< iterator, bool > insert(P &&value);
    iterator insert(constIterator it, const valueType &value);
    template< typename P >
    iterator insert(constIterator, P &&value);
    template< typename InputIterator >
    void insert(InputIterator, InputIterator);
  private:
    ForwardList< valueType > data_;
    Compare comp_;
    sizeType size_;
  };

  template< typename Key, typename T, typename Compare >
  Dictionary< Key, T, Compare >::Dictionary():
    data_(),
    comp_(),
    size_(0)
  {}

  template< typename Key, typename T, typename Compare >
  Dictionary< Key, T, Compare >::Dictionary(const Dictionary< Key, T, Compare > &other):
    data_(other.data_),
    comp_(other.comp_),
    size_(other.size_)
  {}

  template< typename Key, typename T, typename Compare >
  Dictionary< Key, T, Compare >::Dictionary(Dictionary< Key, T, Compare > &&other):
    data_(std::move(other.data_)),
    comp_(std::move(other.comp_)),
    size_(other.size_)
  {
    other.size_ = 0;
  }
}
#endif
