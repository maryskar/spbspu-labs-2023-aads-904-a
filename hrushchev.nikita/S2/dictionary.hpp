#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <utility>
#include "forwardlist.hpp"

template< typename Key, typename Value, typename Compare = std::less< > >
class Dictionary
{
public:
	Dictionary();
	~Dictionary() = default;
private:
	ForwardList< std::pair< Key, Value > > data_;
	Compare compare_;
};

template< typename Key, typename Value, typename Compare >
Dictionary< Key, Value, Compare >::Dictionary():
	data_(),
	compare_()
{
}

#endif