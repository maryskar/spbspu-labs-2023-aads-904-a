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
	class ReverseBidirectionalIterator;

	template< typename Key, typename Value, typename Compare = std::less< Key > >
	class ConstReverseBidirectionalIterator;

	template< typename Key, typename Value, typename Compare = std::less< Key > >
	class BidirectionalIterator: public std::iterator< std::bidirectional_iterator_tag, std::pair< Key, Value > >
	{
	public:
		friend class AVL< Key, Value, Compare >;
		friend class ConstBidirectionalIterator< Key, Value, Compare >;
		friend class ReverseBidirectionalIterator< Key, Value, Compare >;
		friend class ConstReverseBidirectionalIterator< Key, Value, Compare >;

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
			m_ptr(const_cast< tree* >(other.m_ptr))
		{}
		BidirectionalIterator(constIterator&& other):
			m_ptr(const_cast< tree* >(other.m_ptr))
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
	class ReverseBidirectionalIterator: public std::iterator< std::bidirectional_iterator_tag, std::pair< Key, Value > >
	{
	public:
		friend class AVL< Key, Value, Compare >;
		friend class ConstReverseBidirectionalIterator< Key, Value, Compare >;

		using T = typename AVL< Key, Value, Compare >::dataPair;
		using tree = typename AVL< Key, Value, Compare >::tree;
		using basicIterator = BidirectionalIterator< Key, Value, Compare >;
		using constIterator = ConstReverseBidirectionalIterator< Key, Value, Compare >;

		ReverseBidirectionalIterator() noexcept:
			m_ptr(nullptr)
		{}
		explicit ReverseBidirectionalIterator(tree* other) noexcept:
			m_ptr(other)
		{}

		ReverseBidirectionalIterator& operator++() noexcept
		{
			basicIterator res(m_ptr);
			res--;
			m_ptr = res.m_ptr;
			return *this;
		}
		ReverseBidirectionalIterator operator++(int) noexcept
		{
			ReverseBidirectionalIterator prev(m_ptr);
			++(*this);

			return prev;
		}
		ReverseBidirectionalIterator& operator--() noexcept
		{
			basicIterator res(m_ptr);
			res++;
			m_ptr = res.m_ptr;
			return *this;
		}
		ReverseBidirectionalIterator operator--(int) noexcept
		{
			ReverseBidirectionalIterator prev(m_ptr);
			--(*this);

			return prev;
		}

		bool operator==(const ReverseBidirectionalIterator& other) const noexcept
		{
			return (m_ptr == other.m_ptr);
		}
		bool operator!=(const ReverseBidirectionalIterator& other) const noexcept
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

		ReverseBidirectionalIterator(const constIterator& other):
			m_ptr(const_cast< tree* >(other.m_ptr))
		{}
		ReverseBidirectionalIterator(constIterator&& other):
			m_ptr(const_cast< tree* >(other.m_ptr))
		{}
	};

	template< typename Key, typename Value, typename Compare >
	class ConstReverseBidirectionalIterator: public std::iterator< std::bidirectional_iterator_tag, const std::pair< Key, Value > >
	{
	public:
		friend class AVL< Key, Value, Compare >;
		friend class ReverseBidirectionalIterator< Key, Value, Compare >;

		using T = typename AVL< Key, Value, Compare >::dataPair;
		using tree = typename AVL< Key, Value, Compare >::tree;
		using iterator = ReverseBidirectionalIterator< Key, Value, Compare >;
		using basicIterator = BidirectionalIterator< Key, Value, Compare >;

		ConstReverseBidirectionalIterator() noexcept:
			m_ptr(nullptr)
		{}
		ConstReverseBidirectionalIterator(const tree* other) noexcept:
			m_ptr(other)
		{}

		ConstReverseBidirectionalIterator(const iterator& other) noexcept:
			m_ptr(other.m_ptr)
		{}
		ConstReverseBidirectionalIterator(iterator&& other) noexcept:
			m_ptr(other.m_ptr)
		{}

		ConstReverseBidirectionalIterator& operator++() noexcept
		{
			basicIterator res(m_ptr);
			res--;
			m_ptr = res.m_ptr;
			return *this;
		}
		ConstReverseBidirectionalIterator operator++(int) noexcept
		{
			ConstReverseBidirectionalIterator prev(m_ptr);
			++(*this);

			return prev;
		}
		ConstReverseBidirectionalIterator& operator--() noexcept
		{
			basicIterator res(m_ptr);
			res++;
			m_ptr = res.m_ptr;
			return *this;
		}
		ConstReverseBidirectionalIterator operator--(int) noexcept
		{
			ConstReverseBidirectionalIterator prev(m_ptr);
			--(*this);

			return prev;
		}

		bool operator==(const ConstReverseBidirectionalIterator& other) const noexcept
		{
			return (m_ptr == other.m_ptr);
		}
		bool operator!=(const ConstReverseBidirectionalIterator& other) const noexcept
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
		using iterator = BidirectionalIterator< Key, Value, Compare >;
		using constIterator = ConstBidirectionalIterator< Key, Value, Compare >;
		using reverseIterator = ReverseBidirectionalIterator< Key, Value, Compare >;
		using reverseConstIterator = ConstReverseBidirectionalIterator< Key, Value, Compare >;

		AVL():
			m_root(nullptr),
			m_cmp()
		{}
		AVL(const AVL& other):
			m_root(copy(other.m_root)),
			m_cmp()
		{}
		AVL(AVL&& other) noexcept:
			m_root(other.m_root),
			m_cmp(other.m_cmp)
		{
			other.m_root = nullptr;
		}
		~AVL()
		{
			clear();
		}



	private:
		tree* m_root;
		Compare m_cmp;

	}

}

#endif
