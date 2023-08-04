#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <utility>
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <forward-list.hpp>
#include <iterator.hpp>
#include <const-iterator.hpp>
#include <comparator.hpp>

namespace turkin
{
  template< typename Key, typename Value, typename Compare >
  class Dictionary
  {
    using dict_t = std::pair< Key, Value >;
    using dict = Dictionary< Key, Value, Compare >;
    using it = Iterator< dict_t >;
    using cit = ConstIterator< dict_t >;
    public:
      Dictionary();
      Dictionary(const dict & rhs);
      Dictionary(dict && rhs);
      Dictionary(std::initializer_list< dict_t > init);
      Dictionary & operator=(const dict & rhs);
      Dictionary & operator=(dict && rhs);
      ~Dictionary() = default;
      it before_begin() noexcept;
      cit before_begin() const noexcept;
      cit cbefore_begin() const noexcept;
      it begin() noexcept;
      cit begin() const noexcept;
      cit cbegin() const noexcept;
      it end() noexcept;
      cit end() const noexcept;
      cit cend() const noexcept;
      it rbegin() noexcept;
      cit rbegin() const noexcept;
      cit crbegin() const noexcept;
      it rend() noexcept;
      cit rend() const noexcept;
      cit crend() const noexcept;

      bool empty() const noexcept;
      std::size_t size() const noexcept;

      void clear() noexcept;
      std::pair< it, bool > insert(const Key & k, const Value & v);
      std::pair< it, bool > insert(const dict_t & value);
      template< class... Args >
      std::pair< it, bool > emplace(Args &&... args);
      it erase_after(cit pos);
      it erase_after(cit first, cit last);
      std::size_t erase(const Key & k);
      void swap(dict & rhs) noexcept;
      dict_t extract_after(cit pos);
      Value at(const Key & k);
      const Value at(const Key & k) const;

      std::size_t count(const Key & k) const;
      it find(const Key & k);
      cit find(const Key & k) const;
      std::pair< it, it > equal_range(const Key & k);
      std::pair< cit, cit > equal_range(const Key & k) const;
      it lower_bound(const Key & k);
      cit lower_bound(const Key & k) const;
      it upper_bound(const Key & k);
      cit upper_bound(const Key & k) const;

    private:
      ForwardList< dict_t > fl_;
      Compare cmp_;
  };
}

using namespace turkin;

template< typename K, typename V, typename C >
Dictionary< K, V, C >::Dictionary():
  fl_(),
  cmp_()
{}

template< typename K, typename V, typename C >
Dictionary< K, V, C >::Dictionary(const dict & rhs):
  fl_(rhs.fl_),
  cmp_(rhs.cmp_)
{}

template< typename K, typename V, typename C >
Dictionary< K, V, C >::Dictionary(dict && rhs):
  fl_(rhs.fl_),
  cmp_(rhs.cmp_)
{}

template< typename K, typename V, typename C >
Dictionary< K, V, C >::Dictionary(std::initializer_list< dict_t > init):
  fl_(init),
  cmp_()
{}


template< typename K, typename V, typename C >
Dictionary< K, V, C > & Dictionary< K, V, C >::operator=(const dict & rhs)
{
  if (std::addressof(rhs) == this)
  {
    return * this;
  }
  fl_ = rhs.fl_;
  cmp_ = rhs.cmp_;
  return * this;
}

template< typename K, typename V, typename C >
Dictionary< K, V, C > & Dictionary< K, V, C >::operator=(dict && rhs)
{
  if (std::addressof(rhs) == this)
  {
    return * this;
  }
  fl_ = std::move(rhs.fl_);
  cmp_ = rhs.cmp_;
  return * this;
}

template< typename K, typename V, typename C >
Iterator< std::pair< K, V > > Dictionary< K, V, C >::before_begin() noexcept
{
  return fl_.before_begin();
}

template< typename K, typename V, typename C >
ConstIterator< std::pair< K, V > > Dictionary< K, V, C >::before_begin() const noexcept
{
  return fl_.before_begin();
}

template< typename K, typename V, typename C >
ConstIterator< std::pair< K, V > > Dictionary< K, V, C >::cbefore_begin() const noexcept
{
  return fl_.cbefore_begin();
}

template< typename K, typename V, typename C >
Iterator< std::pair< K, V > > Dictionary< K, V, C >::begin() noexcept
{
  return fl_.begin();
}

template< typename K, typename V, typename C >
ConstIterator< std::pair< K, V > > Dictionary< K, V, C >::begin() const noexcept
{
  return fl_.begin();
}

template< typename K, typename V, typename C >
ConstIterator< std::pair< K, V > > Dictionary< K, V, C >::cbegin() const noexcept
{
  return fl_.cbegin();
}

template< typename K, typename V, typename C >
Iterator< std::pair< K, V > > Dictionary< K, V, C >::end() noexcept
{
  return fl_.end();
}

template< typename K, typename V, typename C >
ConstIterator< std::pair< K, V > > Dictionary< K, V, C >::end() const noexcept
{
  return fl_.end();
}

template< typename K, typename V, typename C >
ConstIterator< std::pair< K, V > > Dictionary< K, V, C >::cend() const noexcept
{
  return fl_.cend();
}

template< typename K, typename V, typename C >
Iterator< std::pair< K, V > > Dictionary< K, V, C >::rbegin() noexcept
{
  return fl_.end();
}

template< typename Key, typename Value, typename Compare >
ConstIterator< std::pair< Key, Value > > Dictionary< Key, Value, Compare >::rbegin() const noexcept
{
  return fl_.end();
}

template< typename K, typename V, typename C >
ConstIterator< std::pair< K, V > > Dictionary< K, V, C >::crbegin() const noexcept
{
  return fl_.cend();
}

template< typename K, typename V, typename C >
Iterator< std::pair< K, V > > Dictionary< K, V, C >::rend() noexcept
{
  return fl_.begin();
}

template< typename K, typename V, typename C >
ConstIterator< std::pair< K, V > > Dictionary< K, V, C >::rend() const noexcept
{
  return fl_.begin();
}

template< typename K, typename V, typename C >
ConstIterator< std::pair< K, V > > Dictionary< K, V, C >::crend() const noexcept
{
  return fl_.cbegin();
}

template< typename K, typename V, typename C >
bool Dictionary< K, V, C >::empty() const noexcept
{
  return fl_.empty();
}

template< typename K, typename V, typename C >
std::size_t Dictionary< K, V, C >::size() const noexcept
{
  return fl_.size();
}

template< typename K, typename V, typename C >
void Dictionary< K, V, C >::clear() noexcept
{
  fl_.clear();
}

template< typename K, typename V, typename C >
std::pair< Iterator< std::pair< K, V > >, bool > Dictionary< K, V, C >::insert(const K & k, const V & v)
{
  return insert(std::make_pair(k, v));
}

template< typename K, typename V, typename C >
std::pair< Iterator< std::pair< K, V > >, bool > Dictionary< K, V, C >::insert(const std::pair< K, V > & value)
{
  it ins = lower_bound(value.first);
  return std::make_pair(fl_.insert_after(cit(ins), value), true);
}

template< typename K, typename V, typename C >
template< class... Args >
std::pair< Iterator< std::pair< K, V > >, bool > Dictionary< K, V, C >::emplace(Args &&... args)
{
  return insert(dict_t(std::forward< Args >(args)...));
}

template< typename K, typename V, typename C >
Iterator< std::pair< K, V > > Dictionary< K, V, C >::erase_after(cit pos)
{
  return fl_.erase_after(pos);
}

template< typename K, typename V, typename C >
Iterator< std::pair< K, V > > Dictionary< K, V, C >::erase_after(cit first, cit last)
{
  return fl_.erase_after(first, last);
}

template< typename K, typename V, typename C >
std::size_t Dictionary< K, V, C >::erase(const K & k)
{
  std::size_t amount = 0;
  for (auto ins = cbegin(); ins != cend(); ins++)
  {
    auto temp = ins;
    temp++;
    if (temp != cend())
    {
      if (eq< K, C >(temp->first, k))
      {
        erase_after(ins);
        amount++;
      }
    }
  }
  return amount;
}

template< typename K, typename V, typename C >
void Dictionary< K, V, C >::swap(dict & rhs) noexcept
{
  fl_.swap(rhs.fl_);
  std::swap(cmp_, rhs.cmp_);
}

template< typename K, typename V, typename C >
std::pair< K, V > Dictionary< K, V, C >::extract_after(cit pos)
{
  return *erase_after(pos);
}

template< typename K, typename V, typename C >
V Dictionary< K, V, C >::at(const K & k)
{
  auto ins = find(k);
  if (neq< K, C >(ins->first, k))
  {
    throw std::out_of_range("Out of range");
  }
  return ins->second;
}

template< typename K, typename V, typename C >
const V Dictionary< K, V, C >::at(const K & k) const
{
  return at(k);
}

template< typename K, typename V, typename C >
Iterator< std::pair< K, V > > Dictionary< K, V, C >::find(const K & k)
{
  for (auto ins = begin(); ins != end(); ins++)
  {
    if (eq< K, C >(ins->first, k))
    {
      return ins;
    }
  }
  return end();
}

template< typename K, typename V, typename C >
ConstIterator< std::pair< K, V > > Dictionary< K, V, C >::find(const K & k) const
{
  return cit(find(k));
}

template< typename K, typename V, typename C >
std::pair< Iterator< std::pair< K, V > >, Iterator< std::pair< K, V > > > Dictionary< K, V, C >::equal_range(const K & k)
{
  return std::make_pair(lower_bound(k), upper_bound(k));
}

template< typename K, typename V, typename C >
std::pair< ConstIterator< std::pair< K, V > >, ConstIterator< std::pair< K, V > > > Dictionary< K, V, C >::equal_range(const K & k) const
{
  return std::make_pair(lower_bound(k), upper_bound(k));
}


template< typename K, typename V, typename C >
std::size_t Dictionary< K, V, C >::count(const K & k) const
{
  std::size_t amount = 0;
  for(auto ins = cbegin(); ins != cend(); ins++)
  {
    if (eq< K, C >(ins->first, k))
    {
      amount++;
    }
  }
  return amount;
}

template< typename K, typename V, typename C >
Iterator< std::pair< K, V > > Dictionary< K, V, C >::lower_bound(const K & k)
{
  auto res = fl_.before_begin();
  for (auto it = begin(); it != end() && cmp_(it->first, k); ++it, ++res);
  return res;
}

template< typename K, typename V, typename C >
ConstIterator< std::pair< K, V > > Dictionary< K, V, C >::lower_bound(const K & k) const
{
  return cit(lower_bound(k));
}

template< typename K, typename V, typename C >
Iterator< std::pair< K, V > > Dictionary< K, V, C >::upper_bound(const K & k)
{
  auto res = fl_.before_begin();
  for (auto it = begin(); it != end() && !cmp_(it->first, k); ++it, ++res);
  return res;
}

template< typename K, typename V, typename C >
ConstIterator< std::pair< K, V > > Dictionary< K, V, C >::upper_bound(const K & k) const
{
  return cit(upper_bound(k));
}

#endif
