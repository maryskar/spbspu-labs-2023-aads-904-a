#ifndef STACK_H
#define STACK_H
#include <stdexcept>

template < typename T >
class Stack {
private:
  struct Node {
    T val;
    Node* next;
  };

  Node* top_;

public:
  Stack():
    top_(nullptr)
  {}

  ~Stack()
  {
    Node* tp = nullptr;
    while (top_ != nullptr) {
      tp = top_;
      top_ = top_->next;
      delete tp;
    }
  }

  void push(T rhs)
  {
    Node* node = new Node(rhs);
    node->next = top_;
    top_ = node;
  }

  void pop()
  {
    if (top_ == nullptr) {
      throw std::out_of_range("Stack is empty");
    }
    Node* top = top_;
    top_ = top_->next;
    T val = top->val;
    delete top;
    return val;
  }

  bool empty() const
  {
    return top_ == nullptr;
  }

  size_t size() const
  {
    Node* node = top_;
    size_t count = 0;
    while (node != nullptr) {
      node = node->next;
      count++;
    }
    return count;
  }
};

#endif
