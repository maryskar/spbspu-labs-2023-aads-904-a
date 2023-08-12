#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "forwardList.h"

namespace dmitriev
{
	template< typename Key, typename Value, typename Compare = std::less< > >
	class Dictionary
	{
	public:
		using fListPair = std::pair< Key, Value >;
		using fList = ForwardList< fListPair >;
		using iterator = typename fList::iterator;
		using constIterator = typename fList::constIterator;

		Dictionary():
			m_fList(),
			m_comp()
		{}
		Dictionary(std::initializer_list< fListPair >, const Compare& comp = Compare());//
		Dictionary(const Dictionary& other) = default;
		Dictionary(Dictionary&& other) = default;

		~Dictionary() = default;


		iterator insert(const fListPair& keyValue)
		{
			iterator it = beforeUpperBound(keyValue.first);

			if (it->first == keyValue.first)
			{
				return it;
			}

			return m_fList.insertAfter(it, keyValue);
		}
		iterator insert(fListPair&& keyValue)
		{
			iterator it = beforeUpperBound(keyValue.first);

			if (it->first == keyValue.first)
			{
				return it;
			}

			return m_fList.insertAfter(it, std::move(keyValue));
		}
		template< typename inputIterator >
		void insert(inputIterator first, inputIterator last)
		{
			for (; first != last; first++)
			{
				insert(*first);
			}
		}
		void insert(std::initializer_list< fListPair > initList)
		{
			insert(initList.begin(), initList.end());
		}

		Value& at(const Key& key)
		{
			iterator it = find(key);
			if (!isExist(it))
			{
				throw std::logic_error("no element with such key");
			}
			return it->second;
		}
		const Value& at(const Key& key) const
		{
			iterator it = find(key);
			if (!isExist(it))
			{
				throw std::logic_error("no element with such key");
			}
			return it->second;
		}

		iterator beforeLowerBoard(const Key& key)
		{
			iterator result = beforeBegin();
			for (iterator it = begin(); (it != end()) && m_comp(it->first, key); result++, it++)
			{}

			return result;
		}
		iterator beforeUpperBound(const Key& key)
		{
			iterator result = beforeBegin();
			for (iterator it = begin(); (it != end()) && !m_comp(key, it->first); result++, it++)
			{}

			return result;
		}

		iterator lowerBound(const Key& key)
		{
			return ++beforeLowerBoard(key);
		}
		iterator upperBound(const Key& key)
		{
			return ++beforeUpperBound();
		}

		iterator find(const Key& key)
		{
			iterator result = begin();

			for(; isExist(result) && (result->first != key); result++)
			{}

			return result;
		}

		iterator beforeBegin()
		{
			return m_fList.beforeBegin();
		}
		iterator begin()
		{
			return m_fList.begin();
		}
		iterator end()
		{
			return m_fList.end();
		}

		constIterator constBeforeBegin()
		{
			return m_fList.constBeforeBegin();
		}
		constIterator constBegin()
		{
			return m_fList.constBegin();
		}
		constIterator constEnd()
		{
			return m_fList.constEnd();
		}

		bool isEmpty()
		{
			return m_fList.isEmtpy();
		}
		bool isExist(iterator it)
		{
			return it != end();
		}
		bool isExist(const Key& key)
		{
			return isExist(find(key));
		}


	private:
		fList m_fList;
		Compare m_comp;

	};
}

#endif
