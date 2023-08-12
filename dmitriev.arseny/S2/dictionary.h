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

		Value at(const Key& key)
		{
			iterator it = find(key);
			if (!isExist(it))
			{
				throw std::logic_error("no element with such key");
			}
		}

		iterator lowerBound(const Key& key)
		{
			iterator result;
			for(result = begin(); (result != end()) && m_comp(result->first, key); result++)
			{}

			return result;
		}
		iterator upperBound(const Key& key)
		{
			iterator result;
			for (result = begin(); (result != end()) && !m_comp(key, result->first); result++)
			{}

			return result;
		}

		iterator find(const Key& key)
		{
			iterator result = begin();

			for(; (result != end()) && (result->first =! key); key++)
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
			return it == end();
		}
		bool isExist(const Key& key)
		{
			return isExist(find(key));
		}

		void test()
		{
			std::cout << m_comp(2, 2);
		}

	private:
		fList m_fList;
		Compare m_comp;

	};
}

#endif
