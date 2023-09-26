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

	template< typename T >
	void clear(Tree< T >* root)
	{
		if (isEmpty(root))
		{
			return;
		}

		if (!isEmpty(root->left))
		{
			clear(root->left);
		}
		if (!isEmpty(root->right))
		{
			clear(root->right);
		}

		delete root;
	}

}

#endif
