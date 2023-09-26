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

		AVL& operator=(const AVL& other)
		{
			if (this == std::addressof(other))
			{
				return *this;
			}

			AVL< Key, Value, Compare > newTree(other);
			*this = std::move(newTree);
			return *this;
		}
		AVL& operator=(AVL&& other) noexcept
		{
			if (this == std::addressof(other))
			{
				return *this;
			}

			clear();
			swap(other);
			return *this;
		}

		void insert(const dataPair& keyValue)
		{
			m_root = insertUtil(m_root, keyValue);
		}
		void insert(dataPair&& keyValue)
		{
			insert(keyValue);
		}
		template< typename inputIterator >
		void insert(inputIterator first, inputIterator last)
		{
			for (; first != last; first++)
			{
				insert(*first);
			}
		}
		void insert(std::initializer_list< std::pair< Key, Value > > initList)
		{
			insert(initList.begin(), initList.end());
		}

		Value& at(const Key& key)
		{
			iterator it = find(key);
			if (isEmpty(it))
			{
				throw std::out_of_range("no reseults with such key");
			}

			return it->second;
		}
		const Value& at(const Key& key) const
		{
			constIterator it = constFind(key);
			if (isEmpty(it))
			{
				throw std::out_of_range("no reseults with such key");
			}

			return it->second;
		}

		iterator lowerBound(const Key& key)
		{
			iterator res = begin();

			for (; !isEmpty(res.m_ptr) && m_cmp(res->first, key); res++)
			{}

			return res;
		}
		iterator upperBound(const Key& key)
		{
			iterator res = begin();

			for (; !isEmpty(res.m_ptr) && !m_cmp(key, res->first); res++)
			{}

			return res;
		}
		constIterator constLowerBound(const Key& key) const
		{
			constIterator res = constBegin();

			for (; !isEmpty(res.m_ptr) && m_cmp(res->first, key); res++)
			{}

			return res;
		}
		constIterator constUpperBound(const Key& key) const
		{
			constIterator res = constBegin();

			for (; !isEmpty(res.m_ptr) && !m_cmp(key, res->first); res++)
			{}

			return res;
		}

		iterator find(const Key& key)
		{
			iterator res = begin();

			for (; !isEmpty(res) && !isEqual(res->first, key); res++)
			{}

			return res;
		}
		constIterator constFind(const Key& key) const
		{
			constIterator res = constBegin();

			for (; !isEmpty(res) && !isEqual(res->first, key); res++)
			{}

			return res;
		}

		iterator begin()
		{
			return iterator(min());
		}
		iterator end()
		{
			return iterator();
		}
		constIterator constBegin() const
		{
			return iterator(min());
		}
		constIterator constEnd() const
		{
			return iterator();
		}
		reverseIterator reverseBegin()
		{
			return reverseIterator(max());
		}
		reverseIterator reverseEnd()
		{
			return reverseIterator();
		}
		reverseConstIterator reverseConstBegin() const
		{
			return reverseConstIterator(max());
		}
		reverseConstIterator reverseConstEnd() const
		{
			return reverseConstIterator();
		}

		void clear()
		{
			dmitriev::clear(m_root);
			m_root = nullptr;
		}
		void swap(AVL& other) noexcept
		{
			std::swap(m_root, other.m_root);
		}
		bool isEmpty(constIterator it) const noexcept
		{
			return dmitriev::isEmpty(it.m_ptr);
		}
		bool isEmpty() const noexcept
		{
			return dmitriev::isEmpty(m_root);
		}
		bool isEqual(const Key& lhs, const Key& rhs) const
		{
			return !(Compare{}(rhs, lhs) || Compare{}(lhs, rhs));
		}


	private:
		tree* m_root;
		Compare m_cmp;

		tree* eraseUtil(tree* node, const Key key)
		{
			if (isEmpty(node))
			{
				return nullptr;
			}

			if (isEqual(node->data.first, key))
			{
				if (isEmpty(node->left) && isEmpty(node->right))
				{
					delete node;
					return nullptr;
				}
				else if (isEmpty(node->left))
				{
					tree* temp = node->right;
					delete node;
					return temp;
				}
				else if (isEmpty(node->right))
				{
					tree* temp = node->left;
					delete node;
					return temp;
				}
				else
				{
					tree* minNode = findMin(node->right);
					node->data = minNode->data;
					node->right = eraseUtil(node->right, minNode->data.first);
					if (!isEmpty(node->right))
					{
						node->right->parent = node;
					}
				}
			}
			else if (m_cmp(key, node->data.first))
			{
				node->left = eraseUtil(node->left, key);
				if (!isEmpty(node->left))
				{
					node->left->parent = node;
				}
			}
			else if (!m_cmp(key, node->data.first))
			{
				node->right = eraseUtil(node->right, key);
				if (!isEmpty(node->left))
				{
					node->right->parent = node;
				}
			}

			return balance(node);
		}
		tree* insertUtil(tree* node, const dataPair& keyValue)
		{
			if (isEmpty(node))
			{
				return new tree{keyValue, 1, nullptr, nullptr, nullptr};
			}

			if (isEqual(keyValue.first, node->data.first))
			{
				return node;
			}
			if (m_cmp(keyValue.first, node->data.first))
			{
				node->left = insertUtil(node->left, keyValue);
				node->left->parent = node;
			}
			else if (!m_cmp(keyValue.first, node->data.first))
			{
				node->right = insertUtil(node->right, keyValue);
				node->right->parent = node;
			}

			return balance(node);
		}

		tree* balance(tree* node)
		{
			updateHeight(node);
			int bf = balanceFactor(node);

			if (bf < -1 && balanceFactor(node->right) <= 0)
			{
				return rotateLeft(node);
			}
			if (bf < -1 && balanceFactor(node->right) > 0)
			{
				node->right = rotateRight(node->right);
				return rotateLeft(node);
			}

			if (bf > 1 && balanceFactor(node->left) >= 0)
			{
				return rotateRight(node);
			}
			if (bf > 1 && balanceFactor(node->left) < 0)
			{
				node->left = rotateLeft(node->left);
				return rotateRight(node);
			}

			return node;
		}

		tree* rotateRight(tree* node)
		{
			tree* temp = node->left;
			node->left = temp->right;
			if (!isEmpty(temp->right))
			{
				temp->right->parent = node;
			}
			temp->right = node;
			temp->parent = node->parent;
			if (!isEmpty(node->parent))
			{
				node->parent->right = temp;
			}
			node->parent = temp;

			updateHeight(node);
			updateHeight(temp);

			return temp;
		}
		tree* rotateLeft(tree* node)
		{
			tree* temp = node->right;
			node->right = temp->left;
			if (!isEmpty(temp->left))
			{
				temp->left->parent = node;
			}
			temp->left = node;
			temp->parent = node->parent;
			if (!isEmpty(node->parent))
			{
				node->parent->left = temp;
			}
			node->parent = temp;

			updateHeight(node);
			updateHeight(temp);

			return temp;
		}

		void updateHeight(tree* node) noexcept
		{
			node->height = 1 + std::max(height(node->left), height(node->right));
		}
		int balanceFactor(const tree* node) const noexcept
		{
			if (isEmpty(node))
			{
				return 0;
			}
			return height(node->left) - height(node->right);
		}
		int height(const tree* node) const noexcept
		{
			if (isEmpty(node))
			{
				return 0;
			}
			return node->height;
		}

		tree* max() const noexcept
		{
			return findMax(m_root);
		}
		tree* min() const noexcept
		{
			return findMin(m_root);
		}

		tree* findMax(tree* node) const noexcept
		{
			if (isEmpty(node))
			{
				return nullptr;
			}
			while (!isEmpty(node->right))
			{
				node = node->right;
			}

			return node;
		}
		tree* findMin(tree* node) const noexcept
		{
			if (isEmpty(node))
			{
				return nullptr;
			}
			while (!isEmpty(node->left))
			{
				node = node->left;
			}

			return node;
		}

	}

}

#endif
