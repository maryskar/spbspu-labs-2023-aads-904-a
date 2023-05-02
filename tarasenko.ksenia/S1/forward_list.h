#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H
#include <memory>
#include "node.h"
namespace tarasenko
{
  namespace details
  {
    template< typename T >
    class ForwardList
    {
    public:
     ForwardList():
       first_(nullptr)
     {}
     ForwardList(const ForwardList< T >& other):
       first_(details::newCopy(other.first_))
     {}
     ForwardList(ForwardList< T >&& other):
       first_(other.first_)
     {
       other.first_ = nullptr;
     }
     ForwardList< T >& operator=(const ForwardList< T >& other)
     {
       if (this != std::addressof(other))
       {
         details::NodeOfList< T >* new_node = newCopy(other.first_);
         details::clear(std::addressof(first_));
         first_ = new_node;
       }
       return *this;
     }
     ForwardList< T >& operator=(ForwardList< T >&& other)
     {
       if (this != std::addressof(other))
       {
         details::clear(std::addressof(first_));
         first_ = other.first_;
         other.first_ = nullptr;
       }
       return *this;
     }
     ~ForwardList()
     {
       details::clear(std::addressof(first_));
     }
     bool isEmpty() const;
     void pushFront(const T& data);
     void pushBack(const T& data);
     T getFront() const;
     void popFront();
     void clear();
    private:
     details::NodeOfList< T >* first_;
    };

    template< typename T >
    bool ForwardList< T >::isEmpty() const
    {
      return details::isEmpty(first_);
    }

    template< typename T >
    void ForwardList< T >::pushFront(const T& data)
    {
      details::pushFront(std::addressof(first_), data);
    }

    template< typename T >
    void ForwardList< T >::pushBack(const T& data)
    {
      details::pushBack(std::addressof(first_), data);
    }

    template< typename T >
    T ForwardList< T >::getFront() const
    {
      return details::getFront(first_);
    }

    template< typename T >
    void ForwardList< T >::popFront()
    {
      details::popFront(std::addressof(first_));
    }

    template< typename T >
    void ForwardList< T >::clear()
    {
      details::clear(std::addressof(first_));
    }
  }
}
#endif
