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
    bool empty_() const;
  private:
    T * value_;
}
