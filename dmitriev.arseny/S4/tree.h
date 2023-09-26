#ifndef TREE_H
#define TREE_H

namespace dmitriev
{
	template< typename T >
	struct Tree
	{
		T data;
		int height;

		Tree< T >* parent;
		Tree< T >* left;
		Tree< T >* right;
	};

	template< typename T >
	bool isEmpty(const Tree< T >* node) noexcept
	{
		return node == nullptr;
	}



}

#endif
