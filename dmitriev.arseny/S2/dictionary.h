#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "forwardList.h"

namespace dmitriev
{
	template< typename Key, typename Value, typename Compare >
	class Dictionary
	{
	public:
		using fList = ForwardList< Value >;

	  Dictionary();
		~Dictionary();

		void push(Key k, Value v);
		Value get(Key k);
		Value drop(Key k);

	private:
		fList m_fList;

	};
}

#endif
