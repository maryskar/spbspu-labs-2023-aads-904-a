#ifndef STACK_H
#define STACK_H

#include "list.h"
#include <iomanip>

template< typename T >
class Stack
{
public:
	Stack();
	~Stack();

	Stack(const Stack< T >& otherStack);
	Stack(Stack< T >&& otherStack);

	Stack< T >& operator=(const Stack< T >& otherStack);
	Stack< T >& operator=(Stack< T >&& otherStack);

	void push(T rhs);
	void popBack();
	T getTopData();

	T unsafeGetTopAndPop();

	bool isEmpty();

private:
	List< T >* top;

	void clear();
};

template< typename T >
Stack< T >::Stack() :
	top(nullptr)
{

}

template< typename T >
Stack<T>::~Stack()
{
	clear();
}

template< typename T >
Stack< T >::Stack(const Stack< T >& otherStack) :
	top(nullptr)
{
	if (otherStack.top != nullptr)
	{
		List< T >* otherTop = otherStack.top;
		List< T >* stackTail = nullptr;

		push(otherTop->data);
		stackTail = top;
		otherTop = otherTop->otherList;

		while (otherTop != nullptr)
		{
			stackTail->otherList = new List< T >(otherTop->data);
			stackTail = stackTail->otherList;
			otherTop = otherTop->otherList;
		}
	}
}

template< typename T >
Stack< T >::Stack(Stack< T >&& otherStack) :
	top(otherStack.top)
{
	otherStack.top = nullptr;
}

template< typename T >
Stack< T >& Stack< T >::operator=(const Stack& otherStack)
{
	if (this == &otherStack)
	{
		return *this;
	}
	else if (otherStack.top == nullptr)
	{
		clear();
		top = nullptr;

		return *this;
	}
	Stack< T > newStack;
	List< T >* newStackTail = nullptr;
	List< T >* otherTop = otherStack.top;

	newStack.push(otherTop->data);
	newStackTail = newStack.top;
	otherTop = otherTop->otherList;

	while (otherTop != nullptr)
	{
		newStackTail->otherList = new List< T >(otherTop->data);
		newStackTail = newStackTail->otherList;
		otherTop = otherTop->otherList;
	}

	clear();

	top = newStack.top;
	newStack.top = nullptr;

	return *this;
}

template< typename T >
inline Stack< T >& Stack< T >::operator=(Stack< T >&& otherStack)
{
	if (this == &otherStack)
	{
		return *this;
	}
	top = otherStack.top;
	otherStack.top = nullptr;

	return *this;
}

template< typename T >
void Stack<T>::push(T rhs)
{
	List< T >* newTop = new List< T >(rhs, top);
	top = newTop;
}

template< typename T >
void Stack< T >::popBack()
{
	if (top == nullptr)
	{
		throw std::underflow_error("underflow_error");
	}
	List< T >* currentList = top;
	top = top->otherList;

	delete currentList;
}

template< typename T >
T Stack< T >::getTopData()
{
	if (top == nullptr)
	{
		throw std::underflow_error("underflow_error");
	}
	return top->data;
}

template< typename T >
T Stack< T >::unsafeGetTopAndPop()
{
	T currentData = getTopData();
	popBack();

	return currentData;
}

template< typename T >
bool Stack< T >::isEmpty()
{
	return top == nullptr;
}

template< typename T >
void Stack< T >::clear()
{
	while (!isEmpty())
	{
		popBack();
	}
}

#endif
