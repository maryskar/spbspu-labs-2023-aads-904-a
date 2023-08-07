#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "forwardList.h"

namespace dmitriev
{
	template< typename Key, typename Value, typename Compare >
	class Dictionary;

	template< typename Key, typename Value, typename Compare >
	class ConstDictionaryIterator;

	template< typename Key, typename Value, typename Compare >
	class DictionaryIterator
	{
		friend ConstDictionaryIterator;
		friend Dictionary;

		DictionaryIterator():
			fIterator()
		{}
		DictionaryIterator(const ForwardList< std::pair< Key, Value > > it):
			fIterator(it)
		{}

		DictionaryIterator& operator++()
		{
			fIterator++;
			return *this;
		}
		DictionaryIterator& operator++(int)
		{
			return DictionaryIterator(++fIterator);
		}

		DictionaryIterator& operator*() const
		{
			return fIterator.operator*();
		}
		DictionaryIterator& operator->() const
		{
			return ForwardIterator.operator->();
		}

		bool operator==(const DictionatyIterator& other)
		{
			return (fIterator == other.fIterator);
		}
		bool operator!=(const DictionatyIterator& other)
		{
			return !(*this == other);
		}

	private:
		ForwardList< std::pair< Key, Value > >::iterator fIterator;

	};

	template< typename Key, typename Value, typename Compare >
	class ConstDictionaryIterator
	{
		friend Dictionary;

		ConstDictionaryIterator():
			cFIterator()
		{}
		//DictionaryIterator(const ForwardList< std::pair< Key, Value > > it):
		//	fIterator(it)
		//{}

		//DictionaryIterator& operator++()
		//{
		//	fIterator++;
		//	return *this;
		//}
		//DictionaryIterator& operator++(int)
		//{
		//	return DictionaryIterator(++fIterator);
		//}

		//DictionaryIterator& operator*() const
		//{
		//	return fIterator.operator*();
		//}
		//DictionaryIterator& operator->() const
		//{
		//	return ForwardIterator.operator->();
		//}

		//bool operator==(const DictionatyIterator& other)
		//{
		//	return (fIterator == other.fIterator);
		//}
		//bool operator!=(const DictionatyIterator& other)
		//{
		//	return !(*this == other);
		//}

	private:
		ForwardList< std::pair< Key, Value > >::constIterator cFIterator;

	};

	template< typename Key, typename Value, typename Compare >
	class Dictionary
	{
	public:
		using fList = ForwardList< std::pair< Key, Value > >;

	  Dictionary();
		Dictionary& Dictionary(const Dictionary& other);
		Dictionary& Dictionary(Dictionary&& other);



		~Dictionary() = default;




	private:
		fList m_fList;

	};
}

#endif
