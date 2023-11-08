#ifndef STACK_H
#define STACK_H
#include <stdexcept>
#include <list.h>

namespace chulkov {
  template < typename T >
  class Stack
  {
  public:
    Stack():
      top_(nullptr)
    {}

    Stack(const Stack< T >& other):
      top_(nullptr)
    {
      try {
        if (!other.empty()) {
          List< T >* tp = other.top_;
          List< T >* prev = nullptr;
          while (tp != nullptr) {
            List< T >* newNode = new List< T >(tp->data);
            newNode->next = prev;
            prev = newNode;
            tp = tp->next;
          }
          top_ = prev;
        }
      } catch (...) {
        clear();
        top_ = nullptr;
        throw;
      }
    }

    Stack& operator=(const Stack< T >& other)
    {
      if (this != std::addressof(other)) {
        Stack tp(other);
        std::swap(top_, tp.top_);
      }
      return *this;
    }

    Stack& operator=(Stack< T >&& other)
    {
      if (this != std::addressof(other)) {
        clear();
        top_ = other.top_;
        other.top_ = nullptr;
      }
      return *this;
    }

    Stack(Stack< T >&& other):
      top_(other.top_)
    {
      other.top_ = nullptr;
    }

    ~Stack()
    {
      clear();
    }

    void push(const T& rhs)
    {
      List< T >* newNode = new List< T >{rhs, top_};
      top_ = newNode;
    }

    T& top()
    {
      return const_cast< T& >(static_cast< const Stack& >(*this).top());
    }

    const T& top() const
    {
      if (empty()) {
        throw std::runtime_error("Stack is empty.");
      }
      return top_->data;
    }

    bool empty() const
    {
      return top_ == nullptr;
    }

    void drop()
    {
      if (top_ == nullptr) {
        throw std::out_of_range("Stack is empty");
      }
      List< T >* newhead = top_->next;
      delete top_;
      top_ = newhead;
    }

    void clear()
    {
      while (!empty()) {
        drop();
      }
      top_ = nullptr;
    }

  private:
    List< T >* top_;
  };
}

#endif
