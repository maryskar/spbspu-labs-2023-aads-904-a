#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"
#include <iomanip>

template< typename T >
class Queue
{
public:
	Queue();
	~Queue();

	void push(T rhs);
	void popBack();
	T getTopData();

	T unsafeGetTopAndPop();

	bool isEmpty();

private:
	List< T >* head;
	List< T >* tail;

};

template<typename T>
Queue<T>::Queue() :
	head(nullptr),
	tail(nullptr)
{

}

template<typename T>
Queue<T>::~Queue()
{

}

template< typename T >
void Queue< T >::push(T rhs)
{
	if (head == nullptr)
	{
		head = new List< T >(rhs);
		tail = head;
	}
	else
	{
		tail->otherList = new List< T >(rhs);
		tail = tail->otherList;
	}
}

template< typename T >
void Queue< T >::popBack()
{
	if (head == nullptr)
	{
		throw std::underflow_error("underflow_error");
	}
	List< T >* newHead = head->otherList;
	delete head;

	head = newHead;
}

template<typename T>
T Queue<T>::getTopData()
{
	if (head == nullptr)
	{
		throw std::underflow_error("underflow_error");
	}
	return head->data;
}

template<typename T>
T Queue<T>::unsafeGetTopAndPop()
{
	T currentData = getTopData();
	popBack();

	return T;
}

template<typename T>
inline bool Queue<T>::isEmpty()
{
	return head == nullptr;
}

#endif
