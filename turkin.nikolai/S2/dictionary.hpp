#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <utility>
#include <memory>
#include "forward-list.hpp"
#include "iterator.hpp"
#include "const-iterator.hpp"

namespace turkin
{
  template< typename Key, typename Value, class Compare >
  class Dictionary
  {
    public:
      using dict_t = std::pair< Key, Value >;
      using dict = Dictionary< Key, Value, Compare >;
      using it = Iterator< Value >;
      using cit = ConstIterator< Value >;
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
      //size
      //max_size

      void clear() noexcept; //done
      //insert
      //emplace
      //erase
      //swap
      //extract
      //merge

      //count
      //find
      //equal_range
      //lower_bound
      //upper_bound

    private:
      ForwardList< dict_t > fl_;
  };
}

using namespace turkin;

template< typename Key, typename Value, class Compare >
Dictionary< Key, Value, Compare >::Dictionary():
  fl_()
{}

template< typename Key, typename Value, class Compare >
Dictionary< Key, Value, Compare >::Dictionary(const dict & rhs):
  fl_(rhs.fl_)
{}

template< typename Key, typename Value, class Compare >
Dictionary< Key, Value, Compare >::Dictionary(dict && rhs):
  fl_(rhs.fl_)
{}

template< typename Key, typename Value, class Compare >
Dictionary< Key, Value, Compare > & Dictionary< Key, Value, Compare >::operator=(const dict & rhs)
{
  if (std::addressof(rhs) == this)
  {
    return * this;
  }
  fl_ = rhs.fl_;
  return * this;
}

template< typename Key, typename Value, class Compare >
Dictionary< Key, Value, Compare > & Dictionary< Key, Value, Compare >::operator=(dict && rhs)
{
  if (std::addressof(rhs) == this)
  {
    return * this;
  }
  fl_ = std::move(rhs.fl_);
  return * this;
}

template< typename Key, typename Value, class Compare >
Iterator< Value > Dictionary< Key, Value, Compare >::begin() noexcept
{
  return fl_.begin();
}

template< typename Key, typename Value, class Compare >
ConstIterator< Value > Dictionary< Key, Value, Compare >::begin() const noexcept
{
  return fl_.begin();
}

template< typename Key, typename Value, class Compare >
ConstIterator< Value > Dictionary< Key, Value, Compare >::cbegin() const noexcept
{
  return fl_.cbegin();
}

template< typename Key, typename Value, class Compare >
Iterator< Value > Dictionary< Key, Value, Compare >::end() noexcept
{
  return fl_.end();
}

template< typename Key, typename Value, class Compare >
ConstIterator< Value > Dictionary< Key, Value, Compare >::end() const noexcept
{
  return fl_.end();
}

template< typename Key, typename Value, class Compare >
ConstIterator< Value > Dictionary< Key, Value, Compare >::cend() const noexcept
{
  return fl_.cend();
}

template< typename Key, typename Value, class Compare >
Iterator< Value > Dictionary< Key, Value, Compare >::rbegin() noexcept
{
  return fl_.end();
}

template< typename Key, typename Value, class Compare >
ConstIterator< Value > Dictionary< Key, Value, Compare >::rbegin() const noexcept
{
  return fl_.end();
}

template< typename Key, typename Value, class Compare >
ConstIterator< Value > Dictionary< Key, Value, Compare >::crbegin() const noexcept
{
  return fl_.cend();
}

template< typename Key, typename Value, class Compare >
Iterator< Value > Dictionary< Key, Value, Compare >::rend() noexcept
{
  return fl_.begin();
}

template< typename Key, typename Value, class Compare >
ConstIterator< Value > Dictionary< Key, Value, Compare >::rend() const noexcept
{
  return fl_.begin();
}

template< typename Key, typename Value, class Compare >
ConstIterator< Value > Dictionary< Key, Value, Compare >::crend() const noexcept
{
  return fl_.cbegin();
}

template< typename Key, typename Value, class Compare >
bool Dictionary< Key, Value, Compare >::empty() const noexcept
{
  return fl_.empty();
}

template< typename Key, typename Value, class Compare >
void Dictionary< Key, Value, Compare >::clear() noexcept
{
  fl_.clear();
}

#endif
