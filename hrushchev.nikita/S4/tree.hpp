#ifndef TREE_HPP
#define TREE_HPP

#include <cstddef>  

template< typename T >
struct Tree
{
	T data_;
	Tree< T >* left_;
	Tree< T >* head_;
	Tree< T >* right_;
	size_t height_ = 0;
};

#endif
