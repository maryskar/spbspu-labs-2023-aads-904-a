#ifndef QUEUE_H
#define QUEUE_H

#include <cstddef>
#include <stdexcept>
#include <limits>

template< typename T >
class Queue
{
  public:
    Queue();
		Queue(const Queue & rhs);
		Queue & operator=(const Queue & rhs);
    ~Queue();
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
Queue< T >::Queue():
	value_(new T[10]),
	capacity_(10),
	size_(0)
{}

template< typename T >
Queue< T >::Queue(const Queue< T > & rhs):
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
Queue< T > & Queue< T >::operator=(const Queue< T > & rhs)
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
Queue< T >::~Queue()
{
	delete [] value_;
}

template< typename T >
void Queue< T >::push(T rhs)
{
	if (size_ == capacity_)
	{
  	extend(10);
	}
	value_[size_++] = rhs;
}

template< typename T >
T Queue< T >::drop()
{
	if (isEmpty())
	{
		throw std::logic_error("stack is empty");
	}
	T dpv = value_[--size_];
	return dpv;
}

template< typename T >
bool Queue< T >::isEmpty() const
{
	return size_ == 0;
}

template< typename T >
void Queue< T >::extend(size_t add)
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
