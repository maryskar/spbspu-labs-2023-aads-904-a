#ifndef DICTIONARY_H
#define DICTIONARY_H
#include "ForwardList.h"
namespace timofeev
{
  template< typename Key, typename Value, typename Compare = std::less< Key > >
  class Dictionary
  {
  public:
    using iter = ForwardIterator< std::pair < Key, Value > >;
    using constIter = ForwardConstIterator< std::pair< Key, Value > >;

    void push(Key k, Value v);

    Dictionary();
    ~Dictionary() = default;

    Dictionary(const Dictionary &other);
    Dictionary(Dictionary &&other) noexcept;

    Dictionary< Key, Value, Compare > &operator=(const Dictionary &other);
    Dictionary< Key, Value, Compare > &operator=(Dictionary &&other) noexcept;

    Value &at(const Key &key);
    const Value& at(const Key& key) const;
    Value& operator[](Key&& key);
    Value &operator[](const Key &key);

    iter begin();
    constIter begin() const;
    constIter cbegin() const noexcept;

    iter end();
    constIter end() const;
    constIter cend() const noexcept;

    iter insert(std::pair<  Key, Value > &&value);
    iter insert(const std::pair< Key, Value > &value);
    iter insert( constIter pos, const std::pair<  Key, Value >& value ); //
    template< class P >
    iter insert( constIter pos, P&& value );
    template< typename InputIt >
    void insert(InputIt first, InputIt last);

    iter erase(iter pos);
    iter erase(constIter pos);
    iter erase(iter first, iter last);
    iter erase(constIter first, constIter last);

    void swap(Dictionary< Key, Value, Compare > &other) noexcept;

    size_t count(const Key &key) const;
    iter find(const Key &key);
    constIter find(const Key &key) const;
    bool contains(const Key &key) const;

    bool empty() const noexcept;
    size_t size() const noexcept;
    void clear();

  private:
    ForwardList< std::pair< Key, Value > > data_;
    Compare compare_;
    size_t size_;
  };
