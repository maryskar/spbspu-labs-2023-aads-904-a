#ifndef FORWARDITERATOR_H
#define FORWARDITERATOR_H

#include <iterator>
#include <C:\Users\BlackEvery\source\repos\spbspu-labs-2023-aads-904-a\dmitriev.arseny\common\list.h>

namespace dmitriev
{
	template< typename T >
	class ForwardIterator
	{
	public:
		ForwardIterator(List< T >* ptr);

		ForwardIterator& operator++();
		ForwardIterator& operator++(int);

		bool operator==(const ForwardIterator& other);
		bool operator!=(const ForwardIterator& other);

		const T& operator*();

	private:
		List< T >* m_ptr;

	};
}

namespace dmitriev
{
	class ConstForwardIterator
	{
	public:
		ConstForwardIterator();

	private:

	};
}

template< typename T >
dmitriev::ForwardIterator< T >::ForwardIterator(List< T >* ptr):
	m_ptr(ptr)
{}

template< typename T >
dmitriev::ForwardIterator< T >& dmitriev::ForwardIterator< T >::operator++()
{
	m_ptr = m_ptr->otherList;

	return *this;
}

template< typename T >
dmitriev::ForwardIterator< T >& dmitriev::ForwardIterator< T >::operator++(int)
{
	dmitriev::ForwardIterator< T > currentIterator = *this;
	++(*this);
	return currentIterator;
}

template< typename T >
bool dmitriev::ForwardIterator< T >::operator==(const ForwardIterator& other)
{
	return m_ptr == other.m_ptr;
}

template< typename T >
bool dmitriev::ForwardIterator< T >::operator!=(const ForwardIterator& other)
{
	return !(*this == other);
}

template< typename T >
const T& dmitriev::ForwardIterator< T >::operator*()
{
	return m_ptr->data;
}

#endif
