#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <stdexcept>
#include "forward_list.h"
#include "forward_list_const_iterator.h"
#include "forward_list_iterator.h"

namespace kryuchkova
{
  template< typename Key, typename Value, typename Compare = std::less< > >
  class Dictionary
  {
  public:
    using key_type = Key;
    using val = Value;
    using this_t = Dictionary< Key, Value, Compare >;
    using val_type = std::pair< Key, Value >;
    using iterator = ForwardIterator< val_type >;
    using const_iterator = ConstForwardIterator< val_type >;

    class value_compare;

    Dictionary();
    Dictionary(const this_t & other);
    Dictionary(this_t && other);
    explicit Dictionary(const Compare & comp);
    Dictionary(std::initializer_list< val_type > init, const Compare & comp = Compare());
    template< typename InputIt >
    Dictionary(InputIt first, InputIt last, const Compare & comp = Compare());
    ~Dictionary() = default;

    this_t & operator=(const this_t & other);
    this_t & operator=(this_t && other);
    this_t & operator=(std::initializer_list< val_type > init);
    val & operator[](const key_type & key);
    val & operator[](key_type && key);
    val & at(const key_type & key);
    const val & at(const key_type & key) const;

    iterator before_begin() const noexcept;
    const_iterator cbefore_begin() const noexcept;
    iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;
    iterator end() const noexcept;
    const_iterator cend() const noexcept;
    iterator last() const noexcept;
    const_iterator clast() const noexcept;

    iterator insert(const val_type &);
    template< typename P >
    iterator insert(P &&);

    iterator insert(const_iterator pos, const val_type & val);
    template< typename InputIt >
    void insert(InputIt first, InputIt last);
    iterator erase_after(const_iterator pos);
    iterator erase_after(const_iterator first, const_iterator last);
    iterator find(const key_type & key);
    const_iterator find(const key_type & key) const;

    bool isEmpty() const noexcept;
    bool isEqualTo(const this_t & other) const noexcept;
    void clear() noexcept;
    void insert(std::initializer_list< val_type > init);
    void swap(this_t & other);
    std::size_t size() const noexcept;
    std::size_t erase(const key_type & key);
    std::size_t count(const key_type & key) const;
    value_compare value_comp() const;
    Compare key_comp() const;

  private:
    ForwardList< val_type > data_;
    Compare comp_;
    std::size_t size_;
  };

  template< typename Key, typename Value, typename Compare >
  class Dictionary< Key, Value, Compare >::value_compare
  {
   public:
    bool operator()(const val_type &lhs, const val_type &rhs) const
    {
      return comp(lhs.first, rhs.first);
    };
   protected:
    Compare comp;
  };

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare >::Dictionary():
   data_(),
   comp_(),
   size_(0)
  {}

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare >::Dictionary(const this_t & other):
   data_(other.data_),
   comp_(other.comp_),
   size_(other.size_)
  {}

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare >::Dictionary(this_t && other):
   data_(std::move(other.data_)),
   comp_(std::move(other.comp_)),
   size_(other.size_)
  {
    other.size_ = 0;
  }

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare >::Dictionary(const Compare & comp):
   data_(),
   comp_(comp),
   size_(0)
  {}

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare >::Dictionary(std::initializer_list< val_type > init, const Compare & comp):
   data_(init),
   comp_(comp),
   size_(init.size())
  {}

  template< typename Key, typename Value, typename Compare >
  template< typename InputIt >
  Dictionary< Key, Value, Compare >::Dictionary(InputIt first, InputIt last, const Compare & comp):
   data_(first, last),
   comp_(comp),
   size_(std::abs(std::distance(first, last)))
  {}

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::insert(const val_type & value)
  {
    iterator iter = data_.begin();
    iterator prev = data_.before_begin();
    for (; iter != data_.end(); iter++)
    {
      if (comp_(value.first, (*iter).first))
      {
        break;
      }
      prev = iter;
    }
    if (prev != data_.before_begin() && (prev->first == value.first))
    {
      (*prev).second = value.second;
    }
    else
    {
      data_.insert_after(prev, value);
    }
    return prev;
  }

  template< typename Key, typename Value, typename Compare >
  template< typename P >
  typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::insert(P && value)
  {
    static_assert(std::is_constructible< val_type, P && >::value, "Can`t construct val_t");
    const val_type temp(std::forward< P >(value));
    return insert(temp);
  }

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare > & Dictionary< Key, Value, Compare >::operator=(const this_t & other)
  {
    if (this == std::addressof(other))
    {
      return *this;
    }
    Compare temp = other.comp_;
    data_ = other.data_;
    comp_ = std::move(temp);
    size_ = other.size_;
    return *this;
  }

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare > & Dictionary< Key, Value, Compare >::operator=(this_t && other)
  {
    if (this == std::addressof(other))
    {
      return *this;
    }
    data_ = std::move(other.data_);
    comp_ = std::move(other.comp_);
    size_ = other.size_;
    other.size_ = 0;
    return *this;
  }

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare > & Dictionary< Key, Value, Compare >::operator=(std::initializer_list< val_type > init)
  {
    clear();
    data_ = init;
    comp_ = Compare();
    size_ = init.size();
    return *this;
  }

  template< typename Key, typename Value, typename Compare >
  const Value & Dictionary< Key, Value, Compare >::at(const key_type & key) const
  {
    const_iterator it = find(key);
    if (++it == cend())
    {
      throw std::out_of_range("There is no such key");
    }
    return it->second;
  }

  template< typename Key, typename Value, typename Compare >
  Value & Dictionary< Key, Value, Compare >::at(const key_type & key)
  {
    return const_cast< Value & >((static_cast< const this_t & >(*this)).at(key));
  }


  template< typename Key, typename Value, typename Compare >
  Value & Dictionary< Key, Value, Compare >::operator[](const key_type & key)
  {
    try
    {
      return at(key);
    }
    catch (const std::out_of_range & e)
    {}
    return (*(emplace(key, Value{}).first)).second;
  }

  template< typename Key, typename Value, typename Compare >
  Value & Dictionary< Key, Value, Compare >::operator[](key_type && key)
  {
    return (*this)[key];
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::begin() const noexcept
  {
    return data_.begin();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::const_iterator Dictionary< Key, Value, Compare >::cbegin() const noexcept
  {
    return data_.cbegin();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::end() const noexcept
  {
    return data_.end();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::const_iterator Dictionary< Key, Value, Compare >::cend() const noexcept
  {
    return data_.cend();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::before_begin() const noexcept
  {
    return data_.before_begin();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::const_iterator Dictionary< Key, Value, Compare >::cbefore_begin() const noexcept
  {
    return data_.cbefore_begin();
  }

   template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::last() const noexcept
  {
    return data_.last();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::const_iterator Dictionary< Key, Value, Compare >::clast() const noexcept
  {
    return data_.clast();
  }

  template< typename Key, typename Value, typename Compare >
  template< typename InputIt >
  void Dictionary< Key, Value, Compare >::insert(InputIt first, InputIt last)
  {
    for (; first != last; ++first)
    {
      insert(*first);
    }
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::const_iterator Dictionary< Key, Value, Compare >::find(const key_type & key) const
  {
    iterator curr = begin();
    while (curr != end())
    {
      if (!comp_(curr->first, key) && !comp_(key, curr->first))
      {
        return curr;
      }
      ++curr;
    }
    return cend();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::find(const key_type & key)
  {
    const_iterator cit = (static_cast< const this_t & >(*this)).find(key);
    return data_.erase_after(cit, cit);
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key,
    Value, Compare >::insert(const_iterator pos, const val_type & val)
  {
    Compare comp = key_comp();
    const_iterator moved_pos = pos;
    ++moved_pos;
    if (comp(pos->first, val) && comp(val, moved_pos->first))
    {
      return data_.insert_after(pos, val);
    }
    return insert(val);
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::erase_after(const_iterator pos)
  {
    return data_.erase_after(pos);
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key,
    Value, Compare >::erase_after(const_iterator first, const_iterator last)
  {
    return data_.erase_after(first, last);
  }

  template< typename Key, typename Value, typename Compare >
  std::size_t Dictionary< Key, Value, Compare >::size() const noexcept
  {
    return size_;
  }

  template< typename Key, typename Value, typename Compare >
  void Dictionary< Key, Value, Compare >::clear() noexcept
  {
    data_.clear();
    size_ = 0;
  }

  template< typename Key, typename Value, typename Compare >
  std::size_t Dictionary< Key, Value, Compare >::erase(const key_type & key)
  {
    iterator it = find(key);
    if (it == last())
    {
      return 0ull;
    }
    erase_after(it);
    return 1ull;
  }

  template< typename Key, typename Value, typename Compare >
  void Dictionary< Key, Value, Compare >::swap(this_t & other)
  {
    data_.swap(other.data_);
    std::swap(comp_, other.comp_);
    std::swap(size_, other.size_);
  }

  template< typename Key, typename Value, typename Compare >
  std::size_t Dictionary< Key, Value, Compare >::count(const key_type & key) const
  {
    return ++(find(key)) == end() ? 0ull : 1ull;
  }

  template< typename Key, typename Value, typename Compare >
  void Dictionary< Key, Value, Compare >::insert(std::initializer_list< val_type > init)
  {
    insert(init.begin(), init.end());
  }

  template< typename Key, typename Value, typename Compare >
  bool Dictionary< Key, Value, Compare >::isEqualTo(const this_t & other) const noexcept
  {
    return size_ == other.size_ && data_ == other.data_;
  }

  template< typename Key, typename Value, typename Compare >
  bool Dictionary< Key, Value, Compare >::isEmpty() const noexcept
  {
    return cbegin() == cend();
  }

  template< typename Key, typename Value, typename Compare >
  Compare Dictionary< Key, Value, Compare >::key_comp() const
  {
    return comp_;
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::value_compare Dictionary< Key, Value, Compare >::value_comp() const
  {
    return value_compare(comp_);
  }

}

#endif
