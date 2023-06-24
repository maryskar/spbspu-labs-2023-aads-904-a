#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <utility>
#include <cstddef>
#include <memory>
#include "forward-list.hpp"
#include "iterator.hpp"
#include "const-iterator.hpp"

namespace turkin
{
  template< typename Key, typename Value, typename Compare >
  class Dictionary
  {
    public:
      using dict_t = std::pair< Key, Value >;
      using dict = Dictionary< Key, Value, Compare >;
      using it = Iterator< dict_t >;
      using cit = ConstIterator< dict_t >;
      Dictionary(); //done
      Dictionary(const dict & rhs); //done
      Dictionary(dict && rhs); //done
      Dictionary & operator=(const dict & rhs); //done
      Dictionary & operator=(dict && rhs); //done
      ~Dictionary() = default; //done
      it begin() noexcept; //done
      cit begin() const noexcept; //done
      cit cbegin() const noexcept; //done
      it end() noexcept; //done
      cit end() const noexcept; //done
      cit cend() const noexcept; //done
      it rbegin() noexcept; //done
      cit rbegin() const noexcept; //done
      cit crbegin() const noexcept; //done
      it rend() noexcept; //done
      cit rend() const noexcept; //done
      cit crend() const noexcept; //done

      bool empty() const noexcept; //done
      std::size_t size() const noexcept; //done
      //max_size

      void clear() noexcept; //done
      std::pair< it, bool > insert(const Key & k, const Value & v);
      std::pair< it, bool > insert(const dict_t & value);
      //emplace
      //erase
      //swap
      //extract
      //merge

      std::size_t count(const Key & k) const; //done
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

template< typename Key, typename Value, typename Compare >
Dictionary< Key, Value, Compare >::Dictionary():
  fl_(),
  cmp_()
{}

template< typename Key, typename Value, typename Compare >
Dictionary< Key, Value, Compare >::Dictionary(const dict & rhs):
  fl_(rhs.fl_),
  cmp_(rhs.cmp_)
{}

template< typename Key, typename Value, typename Compare >
Dictionary< Key, Value, Compare >::Dictionary(dict && rhs):
  fl_(rhs.fl_),
  cmp_(rhs.cmp_)
{}

template< typename Key, typename Value, typename Compare >
Dictionary< Key, Value, Compare > & Dictionary< Key, Value, Compare >::operator=(const dict & rhs)
{
  if (std::addressof(rhs) == this)
  {
    return * this;
  }
  fl_ = rhs.fl_;
  cmp_ = rhs.cmp_;
  return * this;
}

template< typename Key, typename Value, typename Compare >
Dictionary< Key, Value, Compare > & Dictionary< Key, Value, Compare >::operator=(dict && rhs)
{
  if (std::addressof(rhs) == this)
  {
    return * this;
  }
  fl_ = std::move(rhs.fl_);
  cmp_ = rhs.cmp_;
  return * this;
}

template< typename Key, typename Value, typename Compare >
Iterator< std::pair< Key, Value > > Dictionary< Key, Value, Compare >::begin() noexcept
{
  return fl_.begin();
}

template< typename Key, typename Value, typename Compare >
ConstIterator< std::pair< Key, Value > > Dictionary< Key, Value, Compare >::begin() const noexcept
{
  return fl_.begin();
}

template< typename Key, typename Value, typename Compare >
ConstIterator< std::pair< Key, Value > > Dictionary< Key, Value, Compare >::cbegin() const noexcept
{
  return fl_.cbegin();
}

template< typename Key, typename Value, typename Compare >
Iterator< std::pair< Key, Value > > Dictionary< Key, Value, Compare >::end() noexcept
{
  return fl_.end();
}

template< typename Key, typename Value, typename Compare >
ConstIterator< std::pair< Key, Value > > Dictionary< Key, Value, Compare >::end() const noexcept
{
  return fl_.end();
}

template< typename Key, typename Value, typename Compare >
ConstIterator< std::pair< Key, Value > > Dictionary< Key, Value, Compare >::cend() const noexcept
{
  return fl_.cend();
}

template< typename Key, typename Value, typename Compare >
Iterator< std::pair< Key, Value > > Dictionary< Key, Value, Compare >::rbegin() noexcept
{
  return fl_.end();
}

template< typename Key, typename Value, typename Compare >
ConstIterator< std::pair< Key, Value > > Dictionary< Key, Value, Compare >::rbegin() const noexcept
{
  return fl_.end();
}

template< typename Key, typename Value, typename Compare >
ConstIterator< std::pair< Key, Value > > Dictionary< Key, Value, Compare >::crbegin() const noexcept
{
  return fl_.cend();
}

template< typename Key, typename Value, typename Compare >
Iterator< std::pair< Key, Value > > Dictionary< Key, Value, Compare >::rend() noexcept
{
  return fl_.begin();
}

template< typename Key, typename Value, typename Compare >
ConstIterator< std::pair< Key, Value > > Dictionary< Key, Value, Compare >::rend() const noexcept
{
  return fl_.begin();
}

template< typename Key, typename Value, typename Compare >
ConstIterator< std::pair< Key, Value > > Dictionary< Key, Value, Compare >::crend() const noexcept
{
  return fl_.cbegin();
}

template< typename Key, typename Value, typename Compare >
bool Dictionary< Key, Value, Compare >::empty() const noexcept
{
  return fl_.empty();
}

template< typename Key, typename Value, typename Compare >
std::size_t Dictionary< Key, Value, Compare >::size() const noexcept
{
  return fl_.size();
}

template< typename Key, typename Value, typename Compare >
void Dictionary< Key, Value, Compare >::clear() noexcept
{
  fl_.clear();
}

template< typename Key, typename Value, typename Compare >
std::pair< Iterator< std::pair< Key, Value > >, bool > Dictionary< Key, Value, Compare >::insert(const Key & k, const Value & v)
{
  return insert(std::make_pair(k, v));
}

template< typename Key, typename Value, typename Compare >
std::pair< Iterator< std::pair< Key, Value > >, bool > Dictionary< Key, Value, Compare >::insert(const std::pair< Key, Value > & value)
{
  /*
  it ins = lower_bound(value.first);
  it moved_ins = ins;
  moved_ins++;
  if (moved_ins == end())
    {
    return std::make_pair(fl_.insert_after(cit(ins), value), true);
  }
  if (moved_ins->first == value.first)
    {
    moved_ins->second = value.second;
    return std::make_pair(moved_ins, false);
  }
  return std::make_pair(fl_.insert_after(cit(ins), value), true);
  */
  fl_.push_front(value);
  return std::make_pair(begin(), true);
}

template< typename Key, typename Value, typename Compare >
std::size_t Dictionary< Key, Value, Compare >::count(const Key & k) const
{
  std::size_t amount = 0;
  auto ins = fl_.before_begin();
  do
  {
    ins++;
    if (ins->first == k)
    {
      amount++;
    }
  }
  while (ins != end());
  return amount;
}

template< typename Key, typename Value, typename Compare >
Iterator< std::pair< Key, Value > > Dictionary< Key, Value, Compare >::lower_bound(const Key & k)
{
  auto res = fl_.before_begin();
  for (auto it = begin(); it != end() && cmp_(it->first, k); ++it, ++res);
  return res;
}

template< typename Key, typename Value, typename Compare >
ConstIterator< std::pair< Key, Value > > Dictionary< Key, Value, Compare >::lower_bound(const Key & k) const
{
  return cit(lower_bound(k));
}

template< typename Key, typename Value, typename Compare >
Iterator< std::pair< Key, Value > > Dictionary< Key, Value, Compare >::upper_bound(const Key & k)
{
  auto res = fl_.before_begin();
  for (auto it = begin(); it != end() && !cmp_(it->first, k); ++it, ++res);
  return res;
}

template< typename Key, typename Value, typename Compare >
ConstIterator< std::pair< Key, Value > > Dictionary< Key, Value, Compare >::upper_bound(const Key & k) const
{
  return cit(upper_bound(k));
}

#endif
