#ifndef FORWARDLISTCONSTITER_H
#define FORWARDLISTCONSTITER_H
#include "ForwardList.h"
#include "ForwardListIter.h"
#include "../common/List.h"
namespace timofeev
{

  template<typename T>
  class ForwardListConstIterator
  {
    friend class ForwardList< T >;
    friend class ForwardListIterator< T >;

  public:
    ForwardListConstIterator();
    ~ForwardListConstIterator() = default;

    ForwardListConstIterator(List<T> *other);
    ForwardListConstIterator(const ForwardListConstIterator <T> &other) = default;
    ForwardListConstIterator(const ForwardListConstIterator <T> &&other) = default;

    bool operator!=(ForwardListConstIterator<T> &other) const;
    bool operator==(ForwardListConstIterator<T> &other) const;

    const T &operator*();
    const T *operator->();

    ForwardListConstIterator<T> &operator++();
    ForwardListConstIterator<T> operator++(int);

  private:
    List<T> *node_;
  };
}

template< typename T>
timofeev::ForwardListConstIterator< T >::ForwardListConstIterator():
  node_(nullptr)
{}

template< typename T >
timofeev::ForwardListConstIterator< T >::ForwardListConstIterator(List< T >* other)
{
  node_ = other;
}

template< typename T >
bool timofeev::ForwardListConstIterator< T >::operator==(ForwardListConstIterator<T> &other) const
{
  return node_ == other.node_;
}

template< typename T >
bool timofeev::ForwardListConstIterator< T >::operator!=(ForwardListConstIterator<T> &other) const
{
  return !(*this == other);
}

template< typename T >
const T& timofeev::ForwardListConstIterator< T >::operator*()
{
  assert(node_ != nullptr);
  return node_->data;
}

template< typename T >
const T* timofeev::ForwardListConstIterator< T >::operator->()
{
  assert(node_ != nullptr);
  return std::addressof(node_->data);
}

template< typename T >
timofeev::ForwardListConstIterator< T >& timofeev::ForwardListConstIterator< T >::operator++()
{
  assert(node_ != nullptr);
  node_ = node_->next;
  return *this;
}

template< typename T >
timofeev::ForwardListConstIterator< T > timofeev::ForwardListConstIterator< T >::operator++(int)
{
  ForwardListIterator< T > tmp(*this);
  assert(node_ != nullptr);
  node_ = node_->next;
  return tmp;
}
#endif
