#ifndef S2_DICTIONARY_H
#define S2_DICTIONARY_H
#include <stdexcept>
#include <utility>
#include "ForwardConstIterator.h"
#include "ForwardIterator.h"
#include "forwardList.h"

namespace mashkin
{
  template< typename T >
  class ForwardConstIterator;
  template< typename T >
  class ForwardIterator;
  template< typename T >
  class ForwardList;

  template< class Key, class Value, class Compare = std::less< Key > >
  class Dictionary
  {
  public:
    using dict = Dictionary< Key, Value, Compare >;
    using key_type = Key;
    using val = Value;
    using value_type = std::pair< const Key, Value >;
    using iter = ForwardIterator< value_type >;
    using const_iter = ForwardConstIterator< value_type >;

    Dictionary();
    explicit Dictionary(const Compare& comp);
    template< class InputIt >
    Dictionary(InputIt first, InputIt last, const Compare& comp);
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

    iter insert(const value_type& value);
    iter insert(value_type&& value);
    template< class InputIt >
    void insert(InputIt first, InputIt last);

    iter erase(iter pos);
    iter erase(const_iter pos);
    iter erase(const_iter first, const_iter last);
    size_t erase(const key_type& key);

    void swap(Dictionary& other) noexcept;

    size_t count(const key_type& key) const;

    iter find(const key_type& key);
    const_iter find(const key_type& key) const;

    bool contains(const key_type& key) const;

  private:
    ForwardList< value_type > pair_;
    Compare comp_;
    size_t size_;
  };

  template< class K, class V, class C >
  size_t Dictionary< K, V, C >::erase(const key_type& key)
  {
    auto var = find(key);
    if (var != end())
    {
      erase(var);
      return 1;
    }
    return 0;
  }

  template< class K, class V, class C >
  typename Dictionary< K, V, C >::iter Dictionary< K, V, C >::erase(const_iter first, const_iter last)
  {
    while (first != last)
    {
      erase(first++);
    }
    return iter(last.node);
  }

  template< class K, class V, class C >
  typename Dictionary< K, V, C >::iter Dictionary< K, V, C >::erase(iter pos)
  {
    return erase(const_iter(pos));
  }

  template< class K, class V, class C >
  typename Dictionary< K, V, C >::iter Dictionary< K, V, C >::erase(const_iter pos)
  {
    if (find(pos->first) == end())
    {
      return end();
    }
    auto toDel = cbegin();
    auto i = pair_.before_begin();
    for (; i != end(); i++)
    {
      if (toDel == pos)
      {
        --size_;
        break;
      }
      toDel++;
    }
    return pair_.erase_after(i);
  }

  template< class K, class V, class C >
  typename Dictionary< K, V, C >::val& Dictionary< K, V, C >::operator[](const key_type& k)
  {
    auto i = cbegin();
    i = find(k);
    if (i == cend())
    {
      insert(std::pair< K, V >(k, V()));
      return find(k)->second;
    }
    return i->second;
  }

  template< class K, class V, class C >
  typename Dictionary< K, V, C >::const_iter Dictionary< K, V, C >::find(const key_type& key) const
  {
    for (auto i = cbegin(); i != cend(); i++)
    {
      if (i->first == key)
      {
        return i;
      }
    }
    return cend();
  }

  template< class K, class V, class C >
  typename Dictionary< K, V, C >::iter Dictionary< K, V, C >::find(const key_type& key)
  {
    auto var = static_cast< const dict& >(*this).find(key);
    return iter(var.node);
  }

  template< class K, class V, class C >
  size_t Dictionary< K, V, C >::count(const key_type& key) const
  {
    return contains(key) ? 1 : 0;
  }

  template< class K, class V, class C >
  bool Dictionary< K, V, C >::contains(const key_type& key) const
  {
    auto res = find(key);
    return res != end();
  }

  template< class K, class V, class C >
  void Dictionary< K, V, C >::swap(Dictionary& other) noexcept
  {
    auto var = other;
    other = *this;
    *this = var;
  }

  template< class K, class V, class C >
  void Dictionary< K, V, C >::clear()
  {
    pair_.clear();
    size_ = 0;
  }

  template< class Key, class Value, class Compare >
  Dictionary< Key, Value, Compare >::Dictionary(Dictionary&& other) noexcept:
    pair_(std::move(other.pair_)),
    comp_(other.comp_),
    size_(other.size_)
  {
  }

  template< class Key, class Value, class Compare >
  template< class InputIt >
  Dictionary< Key, Value, Compare >::Dictionary(InputIt first, InputIt last, const Compare& comp):
    pair_(),
    comp_(comp),
    size_(0)
  {
    insert(first, last);
  }

  template< class K, class V, class C >
  template< class InputIt >
  void Dictionary< K, V, C >::insert(InputIt first, InputIt last)
  {
    for (auto value = first; value != last; value++)
    {
      insert(*value);
    }
  }

  template< class K, class V, class C >
  typename Dictionary< K, V, C >::iter Dictionary< K, V, C >::insert(const value_type& value)
  {
    if (begin() == end())
    {
      pair_.push_front(value);
      size_++;
      return begin();
    }
    auto next = begin();
    {
      for (auto i = pair_.before_begin(); i != end(); i++)
      {
        if (next == end() || comp_(value.first, next->first))
        {
          pair_.insert_after(i, value);
          size_++;
          break;
        }
        next++;
      }
      return next;
    }
  }

  template< class K, class V, class C >
  typename Dictionary< K, V, C >::iter Dictionary< K, V, C >::insert(value_type&& value)
  {
    return insert(value);
  }

  template< class K, class V, class C >
  typename Dictionary< K, V, C >::iter Dictionary< K, V, C >::end() const noexcept
  {
    return pair_.end();
  }

  template< class K, class V, class C >
  typename Dictionary< K, V, C >::val& Dictionary< K, V, C >::at(const key_type& k)
  {
    return const_cast< val& >((static_cast< const dict& >(*this)).at(k));
  }

  template< class K, class V, class C >
  const typename Dictionary< K, V, C >::val& Dictionary< K, V, C >::at(const key_type& k) const
  {
    auto i = cbegin();
    i = find(k);
    if (i == cend())
    {
      throw std::out_of_range("Out of range");
    }
    return i->second;
  }

  template< class K, class V, class C >
  typename Dictionary< K, V, C >::const_iter Dictionary< K, V, C >::cend() const noexcept
  {
    return pair_.cend();
  }

  template< class K, class V, class C >
  typename Dictionary< K, V, C >::const_iter Dictionary< K, V, C >::cbegin() const noexcept
  {
    return pair_.cbegin();
  }

  template< class K, class V, class C >
  size_t Dictionary< K, V, C >::size() const noexcept
  {
    return size_;
  }

  template< class K, class V, class C >
  bool Dictionary< K, V, C >::empty() const noexcept
  {
    return pair_.empty();
  }

  template< class K, class V, class C >
  typename Dictionary< K, V, C >::iter Dictionary< K, V, C >::begin() const noexcept
  {
    return pair_.begin();
  }

  template< class K, class V, class C >
  Dictionary< K, V, C >& Dictionary< K, V, C >::operator=(dict&& rhs) noexcept
  {
    *this = rhs;
    return *this;
  }

  template< class K, class V, class C >
  Dictionary< K, V, C >& Dictionary< K, V, C >::operator=(const dict& rhs)
  {
    clear();
    pair_.insert_after(this->pair_.before_begin(), rhs.pair_.cbegin(), rhs.pair_.cend());
    comp_ = rhs.comp_;
    size_ = rhs.size_;
    return *this;
  }

  template< class K, class V, class C >
  Dictionary< K, V, C >::Dictionary():
    pair_(ForwardList< value_type >()),
    comp_(),
    size_(0)
  {
  }

  template< class K, class V, class C >
  Dictionary< K, V, C >::Dictionary(const C& comp):
    pair_(),
    comp_(comp),
    size_(0)
  {
  }

  template< class K, class V, class C >
  Dictionary< K, V, C >::Dictionary(const Dictionary& other):
    pair_(other.pair_),
    comp_(other.comp_),
    size_(other.size_)
  {
  }
}
#endif
