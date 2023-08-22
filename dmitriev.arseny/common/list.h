#ifndef LIST_H
#define LIST_H

#include<stdexcept>

namespace dmitriev
{
	template< typename T >
	struct List
	{
		T data;
		List< T >* next;
	};

	template< typename T >
	bool isEmpty(const List< T >* list) noexcept
	{
		return list == nullptr;
	}

	template< typename T >
	void clear(List< T >* head) noexcept
	{
		while (!isEmpty(head))
		{
			List< T >* newHead = head->next;
			delete head;

			head = newHead;
		}
	}

	template< typename T >
	std::pair< List< T >*, List< T >* > copy(List< T >* otherHead)
	{
		if (isEmpty(otherHead))
		{
			return std::pair< List< T >*, List< T >* >{nullptr, nullptr};
		}

		List< T >* newHead = new List< T >{otherHead->data};
		List< T >* newTail = newHead;

		while (!isEmpty(otherHead = otherHead->next))
		{
			try
			{
				newTail->next = new List< T >{otherHead->data};
			}
			catch (const std::exception&)
			{
				clear(newHead);
				throw;
			}
			newTail = newTail->next;
		}

		return std::pair< List< T >*, List< T >* >{newHead, newTail};
	}
}

#endif
