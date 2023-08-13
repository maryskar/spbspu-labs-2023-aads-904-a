#ifndef STACK_H
#define STACK_H
#include <stdexcept>

#include "list.h"

namespace chulkov {
  template < typename T >
  class Stack {
  private:
    List< T >* top_;

  public:
    Stack():
      top_(nullptr)
    {}

    T& drop() {
      if (empty()) {
        throw std::runtime_error("Stack is empty.");
      }
      return top_->data;
    }

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

    Stack& operator=(const Stack< T >& other) {
      if (this != &other) {
        Stack tp(other);
        std::swap(top_, tp.top_);
      }
      return *this;
    }

    Stack& operator=(Stack< T >&& other) {
      if (this != &other) {
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

    ~Stack() {
      clear();
    }

    void push(const T& rhs) {
      List< T >* newNode = new List< T >{rhs, top_};
      top_ = newNode;
    }

    const T& drop() const {
      return drop();
    }

    bool empty() const {
      return top_ == nullptr;
    }

    void clear() {
      while (!empty()) {
        if (top_ == nullptr) {
          throw std::out_of_range("Stack is empty");
        }
        T value = top_->data;
        List< T >* top = top_;
        top_ = top_->next;
        delete top;
      }
      top_ = nullptr;
    }
  };
}

#endif
