#ifndef FORWARDLISTCONSTITERATOR_HPP
#define FORWARDLISTCONSTITERATOR_HPP

#include <list.hpp>

template< typename T >
class ForwardListConstIterator
{
	public:
		ForwardListConstIterator();
	private:
		List< T > ptr_;
};

#endif