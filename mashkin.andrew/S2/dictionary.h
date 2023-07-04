#ifndef S2_DICTIONARY_H
#define S2_DICTIONARY_H
#include <utility>
#include "forwardConstIterator.h"
#include "forwardIterator.h"
#include "forwardList.h"

namespace mashkin
{
  template< class Key, class Value, class Compare = std::less< Key > >
  class Dictionary
  {
  public:
    using dict = Dictionary< Key, Value, Compare >;
    using key_type = Key;
    using value_type = std::pair< const Key, Value >;
    using iter = forwardIterator< Value >;
    using const_iter = forwardConstIterator< Value >;

    Dictionary();
    explicit Dictionary(const Compare& comp);
    /*template< class InputIt >
    Dictionary(InputIt first, InputIt last, const Compare& comp);*/
    Dictionary(const Dictionary& other);
    Dictionary(Dictionary&& other) noexcept;

    ~Dictionary() = default;

    dict& operator=(const Dictionary& rhs);
    dict& operator=(Dictionary&& rhs) noexcept;

    Value& at(key_type);
    Value& operator[](key_type);

    iter begin();
    const_iter cbegin();

    iter end();
    const_iter cend();

    bool empty() const noexcept;
    size_t size() const noexcept;

    void clear();

    /*void push(Key k, Value v);
    void drop(Key k);*/

  private:
    ForwardList< value_type > pair_;
    Compare comp_;
    size_t size_;
  };

  template< class Key, class Value, class Compare >
  size_t Dictionary< Key, Value, Compare >::size() const noexcept
  {
    return size_;
  }

  template< class Key, class Value, class Compare >
  bool Dictionary< Key, Value, Compare >::empty() const noexcept
  {
    return pair_.empty();
  }

  template< class Key, class Value, class Compare >
  Dictionary< Key, Value, Compare >::iter Dictionary< Key, Value, Compare >::begin()
  {
    return;
  }

  template< class Key, class Value, class Compare >
  Dictionary< Key, Value, Compare >&
  Dictionary< Key, Value, Compare >::operator=(Dictionary< Key, Value, Compare >&& rhs) noexcept
  {
    *this = std::move(rhs);
    return *this;
  }

  template< class Key, class Value, class Compare >
  Dictionary< Key, Value, Compare >&
  Dictionary< Key, Value, Compare >::operator=(const Dictionary< Key, Value, Compare >& rhs)
  {
    pair_(this->pair_.insert_after(this->pair_.before_begin(), rhs.pair_.cbegin), rhs.pair_.cend());
    comp_ = rhs.comp_;
    size_ = rhs.size_;
    return *this;
  }

  template< class Key, class Value, class Compare >
  Dictionary< Key, Value, Compare >::Dictionary():
    pair_(),
    comp_(),
    size_(0)
  {
  }

  template< class Key, class Value, class Compare >
  Dictionary< Key, Value, Compare >::Dictionary(const Compare& comp):
    pair_(),
    comp_(comp),
    size_(0)
  {
  }

  template< class Key, class Value, class Compare >
  Dictionary< Key, Value, Compare >::Dictionary(const Dictionary& other):
    pair_(other.pair_),
    comp_(other.comp_),
    size_(other.size_)
  {
  }

  template< class Key, class Value, class Compare >
  Dictionary< Key, Value, Compare >::Dictionary(Dictionary&& other) noexcept:
    pair_(std::move(other.pair_)),
    comp_(other.comp_),
    size_(other.size_)
  {
  }

  /*template< class Key, class Value, class Compare >
  template< class InputIt >
  Dictionary< Key, Value, Compare >::Dictionary(InputIt first, InputIt last, const Compare& comp)
  {
  }*/

  /*template< class Key, class Value, class Compare >
  void Dictionary< Key, Value, Compare >::push(Key k, Value v)
  {
    std::pair< Key, Value > pair{k, v};
    pair_.push_front(pair);
  }*/

}
#endif
