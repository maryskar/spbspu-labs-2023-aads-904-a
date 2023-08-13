#ifndef DICTIONARYOFDICTIONARY_H
#define DICTIONARYOFDICTIONARY_H

#include "dictionary.h"

namespace dmitriev
{
	template< typename Key, typename Value, typename Compare = std::less< > >
	class DictionaryOfDictionary
	{
	public:
		DictionaryOfDictionary();
		~DictionaryOfDictionary();

	private:
		Dictionary< std::string, Dictionary< Key, Value > > dicOfDic;

	};
}

#endif
