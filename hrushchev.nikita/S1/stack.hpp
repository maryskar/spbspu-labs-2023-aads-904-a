#ifndef STACK_HPP
#define STACK_HPP

template< typename T >
class Stack
{
  public:
    Stack();
    ~Stack();
    void putInTheStack(const T& value);
    void popOutOfTheStack();
    T& getInStack();
    T drop();
    bool isEmpty() const;
  private:
    T * value_;
}

#endif
