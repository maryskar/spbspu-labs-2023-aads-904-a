#ifndef AVL_H
#define AVL_H

#include "tree.h"

namespace dmitriev
{

	template< typename Key, typename Value, typename Compare = std::less< Key > >
	class AVL;

	template< typename Key, typename Value, typename Compare = std::less< Key > >
	class ConstBidirectionalIterator;

	template< typename Key, typename Value, typename Compare = std::less< Key > >
	class BidirectionalIterator: public std::iterator< std::bidirectional_iterator_tag, std::pair< Key, Value > >
	{
	public:
		friend class AVL< Key, Value, Compare >;
		friend class ConstBidirectionalIterator< Key, Value, Compare >;

		using T = typename AVL< Key, Value, Compare >::dataPair;
		using tree = typename AVL< Key, Value, Compare >::tree;
		using constIterator = ConstBidirectionalIterator< Key, Value, Compare >;

		BidirectionalIterator();
		explicit BidirectionalIterator(tree* other);
		BidirectionalIterator& operator++();
		BidirectionalIterator operator++(int);
		BidirectionalIterator& operator--();
		BidirectionalIterator operator--(int);

		bool operator==(const BidirectionalIterator& other) const;
		bool operator!=(const BidirectionalIterator& other) const;

		T& operator*();
		T* operator->();

	private:
		tree* m_ptr;

	}

	template< typename Key, typename Value, typename Compare >
	class AVL
	{
	public:
		using dataPair = std::pair< Key, Value >;
		using tree = Tree< dataPair >;


	private:
		tree* m_root;
		Compare m_cmp;

	}

}

#endif
