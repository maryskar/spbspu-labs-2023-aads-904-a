#ifndef S2_DICTIONARY_H
#define S2_DICTIONARY_H
#include <stdexcept>
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
    using val = Value;
    using value_type = std::pair< const Key, Value >;
    using iter = forwardIterator< value_type >;
    using const_iter = forwardConstIterator< value_type >;

    Dictionary();
    explicit Dictionary(const Compare& comp);
    /*template< class InputIt >
    Dictionary(InputIt first, InputIt last, const Compare& comp);*/
    Dictionary(const Dictionary& other);
    Dictionary(Dictionary&& other) noexcept;

    ~Dictionary() = default;

    dict& operator=(const Dictionary& rhs);
    dict& operator=(Dictionary&& rhs) noexcept;

    val& at(const key_type& k);
    const val& at(const key_type& k) const;
    val& operator[](const key_type& k);

    iter begin() const noexcept;
    const_iter cbegin() const noexcept;

    iter end() const noexcept;
    const_iter cend() const noexcept;

    bool empty() const noexcept;
    size_t size() const noexcept;

    void clear();

    std::pair< iter, bool > insert(const value_type& value);
    std::pair< iter, bool > insert(value_type&& value);
    template< class InputIt >
    void insert(InputIt first, InputIt last);


    /*void push(Key k, Value v);
    void drop(Key k);*/

  private:
    ForwardList< value_type > pair_;
    Compare comp_;
    size_t size_;
  };

  template< class Key, class Value, class Compare >
  using dict = Dictionary< Key, Value, Compare >;

  template< class K, class V, class C >
  dict< K, V, C >::iter dict< K, V, C >::end() const noexcept
  {
    return pair_.end();
  }

  template< class K, class V, class C >
  dict< K, V, C >::val& dict< K, V, C >::at(const key_type& k)
  {
    return at(k);
  }

  template< class K, class V, class C >
  const dict< K, V, C >::val& dict< K, V, C >::at(const key_type& k) const
  {
    auto i = cbegin();
    for (; i < cend(); i++)
    {
      if (i->first == k)
      {
        return i->second;
      }
    }
    if (i == cend())
    {
      throw std::out_of_range("Out of range");
    }
  }

  template< class K, class V, class C >
  dict< K, V, C >::const_iter dict< K, V, C >::cend() const noexcept
  {
    return pair_.cend();
  }

  template< class K, class V, class C >
  dict< K, V, C >::const_iter dict< K, V, C >::cbegin() const noexcept
  {
    return pair_.cbegin();
  }

  template< class K, class V, class C >
  size_t dict< K, V, C >::size() const noexcept
  {
    return size_;
  }

  template< class K, class V, class C >
  bool dict< K, V, C >::empty() const noexcept
  {
    return pair_.empty();
  }

  template< class K, class V, class C >
  dict< K, V, C >::iter dict< K, V, C >::begin() const noexcept
  {
    return pair_.begin();
  }

  template< class K, class V, class C >
  dict< K, V, C >& dict< K, V, C >::operator=(dict&& rhs) noexcept
  {
    *this = std::move(rhs);
    return *this;
  }

  template< class K, class V, class C >
  dict< K, V, C >& dict< K, V, C >::operator=(const dict& rhs)
  {
    pair_(this->pair_.insert_after(this->pair_.before_begin(), rhs.pair_.cbegin), rhs.pair_.cend());
    comp_ = rhs.comp_;
    size_ = rhs.size_;
    return *this;
  }

  template< class K, class V, class C >
  dict< K, V, C >::Dictionary():
    pair_(),
    comp_(),
    size_(0)
  {
  }

  template< class K, class V, class C >
  dict< K, V, C >::Dictionary(const C& comp):
    pair_(),
    comp_(comp),
    size_(0)
  {
  }

  template< class K, class V, class C >
  dict< K, V, C >::Dictionary(const Dictionary& other):
    pair_(other.pair_),
    comp_(other.comp_),
    size_(other.size_)
  {
  }

  template< class K, class V, class C >
  dict< K, V, C >::Dictionary(Dictionary&& other) noexcept:
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
