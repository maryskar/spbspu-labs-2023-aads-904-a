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

      void clear() noexcept; //done
      std::pair< it, bool > insert(const Key & k, const Value & v); //done
      std::pair< it, bool > insert(const dict_t & value); //done
      template< class... Args >
      std::pair< it, bool > emplace(Args &&... args); //done
      it erase_after(cit pos); //done
      it erase_after(cit first, cit last); //done
      std::size_t erase(const Key & k); //done
      void swap(dict & rhs) noexcept; //done
      dict_t extract_after(cit pos); //done

      std::size_t count(const Key & k) const; //done
      it find(const Key & k); //done
      cit find(const Key & k) const; //done
      std::pair< it, it > equal_range(const Key & k); //done
      std::pair< cit, cit > equal_range(const Key & k) const; //done
      it lower_bound(const Key & k); //done
      cit lower_bound(const Key & k) const; //done
      it upper_bound(const Key & k); //done
      cit upper_bound(const Key & k) const; //done

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
  it ins = lower_bound(value.first);
  return std::make_pair(fl_.insert_after(cit(ins), value), true);
}

template< typename Key, typename Value, typename Compare >
template< class... Args >
std::pair< Iterator< std::pair< Key, Value > >, bool > Dictionary< Key, Value, Compare >::emplace(Args &&... args)
{
  return insert(dict_t(std::forward< Args >(args)...));
}

template< typename Key, typename Value, typename Compare >
Iterator< std::pair< Key, Value > > Dictionary< Key, Value, Compare >::erase_after(cit pos)
{
  return fl_.erase_after(pos);
}

template< typename Key, typename Value, typename Compare >
Iterator< std::pair< Key, Value > > Dictionary< Key, Value, Compare >::erase_after(cit first, cit last)
{
  return fl_.erase_after(first, last);
}

template< typename Key, typename Value, typename Compare >
std::size_t Dictionary< Key, Value, Compare >::erase(const Key & k)
{
  std::size_t amount = 0;
  for (auto ins = cbegin(); ins != cend(); ins++)
  {
    auto temp = ins;
    temp++;
    if (temp != cend())
    {
      if (temp->first == k)
      {
        erase_after(ins);
        amount++;
      }
    }
  }
  return amount;
}

template< typename Key, typename Value, typename Compare >
void Dictionary< Key, Value, Compare >::swap(dict & rhs) noexcept
{
  fl_.swap(rhs.fl_);
  std::swap(cmp_, rhs.cmp_);
}

template< typename Key, typename Value, typename Compare >
std::pair< Key, Value > Dictionary< Key, Value, Compare >::extract_after(cit pos)
{
  return *erase_after(pos);
}

template< typename Key, typename Value, typename Compare >
Iterator< std::pair< Key, Value > > Dictionary< Key, Value, Compare >::find(const Key & k)
{
  for (auto ins = begin(); ins != end(); ins++)
  {
    if(ins->first == k)
    {
      return ins;
    }
  }
  return end();
}

template< typename Key, typename Value, typename Compare >
ConstIterator< std::pair< Key, Value > > Dictionary< Key, Value, Compare >::find(const Key & k) const
{
  return cit(find(k));
}

template< typename Key, typename Value, typename Compare >
std::pair< Iterator< std::pair< Key, Value > >, Iterator< std::pair< Key, Value > > > Dictionary< Key, Value, Compare >::equal_range(const Key & k)
{
  return std::make_pair(lower_bound(k), upper_bound(k));
}

template< typename Key, typename Value, typename Compare >
std::pair< ConstIterator< std::pair< Key, Value > >, ConstIterator< std::pair< Key, Value > > > Dictionary< Key, Value, Compare >::equal_range(const Key & k) const
{
  return std::make_pair(lower_bound(k), upper_bound(k));
}


template< typename Key, typename Value, typename Compare >
std::size_t Dictionary< Key, Value, Compare >::count(const Key & k) const
{
  std::size_t amount = 0;
  for(auto ins = cbegin(); ins != cend(); ins++)
  {
    if (ins->first == k)
    {
      amount++;
    }
  }
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
