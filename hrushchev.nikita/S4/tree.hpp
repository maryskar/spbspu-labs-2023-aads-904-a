#ifndef TREE_HPP
#define TREE_HPP

template< typename T >
struct Tree
{
	T data;
	Tree< T >* left;
	Tree< T >* head;
	Tree< T >* right;
	size_t height = 0;
};

#endif
