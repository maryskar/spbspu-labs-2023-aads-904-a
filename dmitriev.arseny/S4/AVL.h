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

		BidirectionalIterator() noexcept:
			m_ptr(nullptr)
		{}
		explicit BidirectionalIterator(tree* other) noexcept:
			m_ptr(other)
		{}

		BidirectionalIterator& operator++() noexcept
		{
			if (isEmpty(m_ptr))
			{
				return *this;
			}

			if (!isEmpty(m_ptr->right))
			{
				m_ptr = m_ptr->right;
				while (!isEmpty(m_ptr->left))
				{
					m_ptr = m_ptr->left;
				}
			}
			else
			{
				tree* parent = m_ptr->parent;
				while (!isEmpty(parent) && (m_ptr == parent->right))
				{
					m_ptr = parent;
					parent = parent->parent;
				}
				m_ptr = parent;
			}

			return *this;
		}
		BidirectionalIterator operator++(int) noexcept
		{
			BidirectionalIterator prev(m_ptr);
			++(*this);

			return prev;
		}
		BidirectionalIterator& operator--() noexcept
		{
			if (isEmpty(m_ptr))
			{
				return *this;
			}

			if (!isEmpty(m_ptr->left))
			{
				m_ptr = m_ptr->left;
				while (!isEmpty(m_ptr->right))
				{
					m_ptr = m_ptr->right;
				}
			}
			else
			{
				tree* parent = m_ptr->parent;
				while (!isEmpty(parent) && m_ptr == parent->left)
				{
					m_ptr = parent;
					parent = parent->parent;
				}

				m_ptr = parent;
			}

			return *this;
		}
		BidirectionalIterator operator--(int) noexcept
		{
			BidirectionalIterator prev(m_ptr);
			--(*this);

			return prev;
		}

		bool operator==(const BidirectionalIterator& other) const noexcept
		{
			return (m_ptr == other.m_ptr);
		}
		bool operator!=(const BidirectionalIterator& other) const noexcept
		{
			return !(*this == other);
		}

		T& operator*()
		{
			return m_ptr->data;
		}
		T* operator->()
		{
			return std::addressof(m_ptr->data);
		}

	private:
		tree* m_ptr;

		BidirectionalIterator(const constIterator& other):
			m_ptr(const_cast<tree*>(other.m_ptr))
		{}
		BidirectionalIterator(constIterator&& other):
			m_ptr(const_cast<tree*>(other.m_ptr))
		{}
	};


	template< typename Key, typename Value, typename Compare >
	class ConstBidirectionalIterator: public std::iterator< std::bidirectional_iterator_tag, const std::pair< Key, Value > >
	{
	public:
		friend class AVL< Key, Value, Compare >;
		friend class BidirectionalIterator< Key, Value, Compare >;

		using T = typename AVL< Key, Value, Compare >::dataPair;
		using tree = typename AVL< Key, Value, Compare >::tree;
		using iterator = BidirectionalIterator< Key, Value, Compare >;

		ConstBidirectionalIterator() noexcept:
			m_ptr(nullptr)
		{}
		ConstBidirectionalIterator(const tree* other) noexcept:
			m_ptr(other)
		{}

		ConstBidirectionalIterator(const iterator& other) noexcept:
			m_ptr(other.m_ptr)
		{}
		ConstBidirectionalIterator(iterator&& other) noexcept:
			m_ptr(other.m_ptr)
		{}

		ConstBidirectionalIterator& operator++() noexcept
		{
			iterator res(m_ptr);
			res++;
			m_ptr = res.m_ptr;
			return *this;
		}
		ConstBidirectionalIterator operator++(int) noexcept
		{
			ConstBidirectionalIterator prev(m_ptr);
			++(*this);

			return prev;
		}
		ConstBidirectionalIterator& operator--() noexcept
		{
			iterator res(m_ptr);
			res--;
			m_ptr = res.m_ptr;
			return *this;
		}
		ConstBidirectionalIterator operator--(int) noexcept
		{
			ConstBidirectionalIterator prev(m_ptr);
			--(*this);

			return prev;
		}

		bool operator==(const ConstBidirectionalIterator& other) const noexcept
		{
			return (m_ptr == other.m_ptr);
		}
		bool operator!=(const ConstBidirectionalIterator& other) const noexcept
		{
			return !(*this == other);
		}

		const T& operator*() const
		{
			return m_ptr->data;
		}
		const T* operator->() const
		{
			return std::addressof(m_ptr->data);
		}

	private:
		const tree* m_ptr;

	};


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
