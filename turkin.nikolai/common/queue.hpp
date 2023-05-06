#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <cstring>
#include <stdexcept>
#include "s-q-help.hpp"
#include "oneway-list.hpp"

namespace turkin
{
  template< typename T >
  class Queue
  {
    public:
      Queue();
      Queue(const Queue< T > & rhs);
      Queue(Queue< T > && rhs);
      Queue & operator=(const Queue< T > & rhs);
      Queue & operator=(Queue< T > && rhs);
      ~Queue();
      void swap(Queue< T > & rhs) noexcept;
      void push(const T & rhs);
      T drop();
      T drop() const;
      bool isEmpty() const;
    private:
      pattern::OneWayNode< T > * value_;
      pattern::OneWayNode< T > * back_;
  };
}

template< typename T >
turkin::Queue< T >::Queue():
  value_(nullptr),
  back_(nullptr)
{}

template< typename T >
turkin::Queue< T >::Queue(const Queue< T > & rhs):
  value_(nullptr),
  back_(nullptr)
{
  value_ = turkin::pattern::copyList(rhs.value_);
  pattern::OneWayNode< T > * element = value_;
  while (element->next)
  {
    element = element->next;
  }
  back_ = element;
}

template< typename T >
turkin::Queue< T >::Queue(Queue< T > && rhs):
  value_(rhs.value_),
  back_(rhs.back_)
{
  rhs.value_ = nullptr;
  rhs.back_ = nullptr;
}

template< typename T >
turkin::Queue< T > & turkin::Queue< T >::operator=(const turkin::Queue< T > & rhs)
{
  Queue< T > temp(rhs);
  swap(temp);
  return * this;
}

template< typename T >
turkin::Queue< T > & turkin::Queue< T >::operator=(turkin::Queue< T > && rhs)
{
  turkin::sqhelp::free(value_);
  value_ = nullptr;
  back_ = nullptr;
  swap(rhs);
  return * this;
}

template< typename T >
turkin::Queue< T >::~Queue()
{
  turkin::sqhelp::free(value_);
  back_ = nullptr;
}

template< typename T >
void turkin::Queue< T >::swap(Queue< T > & rhs) noexcept
{
  std::swap(value_, rhs.value_);
  std::swap(back_, rhs.back_);
}

template< typename T >
void turkin::Queue< T >::push(const T & rhs)
{
  pattern::OneWayNode< T > * element = new pattern::OneWayNode< T > {rhs, nullptr};
  if (isEmpty())
  {
    value_ = element;
    back_ = element;
    value_->next = back_;
  }
  else
  {
    back_->next = element;
    back_ = back_->next;
  }
}

template< typename T >
T turkin::Queue< T >::drop()
{
  if (isEmpty())
  {
    throw std::runtime_error("queue is empty");
  }
  pattern::OneWayNode< T > * element = nullptr;
  if (value_ == back_)
  {
    element = value_;
    value_ = nullptr;
    back_ = nullptr;
  }
  else
  {
    element = value_;
    value_ = value_->next;
  }
  T ret(element->data);
  delete element;
  return ret;
}

template< typename T >
T turkin::Queue< T >::drop() const
{
  if (isEmpty())
  {
    throw std::runtime_error("queue is empty");
  }
  pattern::OneWayNode< T > * element = nullptr;
  if (value_ == back_)
  {
    element = value_;
    value_ = nullptr;
    back_ = nullptr;
  }
  else
  {
    element = value_;
    value_ = value_->next;
  }
  T ret(element->data);
  delete element;
  return ret;
}

template< typename T >
bool turkin::Queue< T >::isEmpty() const
{
  return value_ == nullptr;
}

#endif
