#ifndef STACK_H
#define STACK_H

#include <cstddef>
#include <stdexcept>
#include <limits>

template< typename T >
class Stack
{
  public:
    Stack();
		Stack(const Stack & rhs);
		Stack & operator=(const Stack & rhs);
    ~Stack();
    void push(T rhs);
    T drop();
		bool isEmpty() const;
  private:
		void extend(size_t add);
    T * value_;
		size_t capacity_;
		size_t size_;
};

template< typename T >
Stack< T >::Stack():
	value_(new T[10]),
	capacity_(10),
	size_(0)
{}

template< typename T >
Stack< T >::Stack(const Stack< T > & rhs):
	value_(new T[rhs.capacity_]),
	capacity_(rhs.capacity_),
	size_(rhs.size_)
{
	for (size_t i = 0; i < size_; i++)
	{
		try
		{
			value_[i] = rhs.value_[i];
		}
		catch (...)
		{
			delete [] value_;
		}
	}
}

template< typename T >
Stack< T > & Stack< T >::operator=(const Stack< T > & rhs)
{
	T * clone = new T[rhs.size_];
	for (size_t i = 0; i < rhs.size_; i++)
	{
		try
		{
			clone[i] = rhs.value_[i];
		}
		catch (...)
		{
			delete [] clone;
			throw;
		}
	}
	delete [] value_;
	value_ = clone;
	size_ = rhs.size_;
	capacity_ = rhs.capacity_;
	return * this;
}

template< typename T >
Stack< T >::~Stack()
{
	delete [] value_;
}

template< typename T >
void Stack< T >::push(T rhs)
{
	if (size_ == capacity_)
	{
  	extend(10);
	}
	value_[size_++] = rhs;
}

template< typename T >
T Stack< T >::drop()
{
	if (isEmpty())
	{
		throw std::logic_error("stack is empty");
	}
	T dpv = value_[--size_];
	return dpv;
}

template< typename T >
bool Stack< T >::isEmpty() const
{
	return size_ == 0;
}

template< typename T >
void Stack< T >::extend(size_t add)
{
	if (capacity_ + add == std::numeric_limits< size_t >::max())
	{
		throw std::overflow_error("stack capacity is over");
	}
	capacity_ = capacity_ + add;
	T * extra = new T[capacity_];
	for (size_t i = 0; i < size_; i++)
	{
		extra[i] = value_[i];
	}
	delete [] value_;
	value_ = extra;
}

#endif
