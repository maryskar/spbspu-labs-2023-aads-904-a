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

template< typename T >
size_t getHeight(const Tree< T >* tree)
{
	if (tree)
	{
		return tree->height_;
	}
	return 0ull;
}

template< typename T >
Tree< T >* getMax(Tree< T >* tree)
{
	if (!tree->right_)
	{
		return tree;
	}
	return getMax(tree->right_);
}

template< typename T >
Tree< T >* getMin(Tree< T >* tree)
{
	if (!tree->left_)
	{
		return tree;
	}
	return getMin(tree->left_);
}

#endif
