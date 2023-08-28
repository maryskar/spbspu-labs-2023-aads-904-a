#ifndef SPBSPU_LABS_2023_AADS_904_A_FORWARDLIST_H
#define SPBSPU_LABS_2023_AADS_904_A_FORWARDLIST_H
#include <cstddef>
#include "ForwardListIter.h"
#include <List.h>
namespace timofeev
{
    template< typename T>
    class ForwardList
    {
    public:
        using iter = ForwardListIter< T >;
        using constIter = ForwardListConstIter< T >;

        ForwardList();
        ~ForwardList();

        ForwardList(const ForwardList< T > &lhs);  //
        ForwardList(ForwardList< T > &&rhs) noexcept;
        ForwardList< T > &operator=(const ForwardList< T > &rhs);
        ForwardList< T > &operator=(ForwardList< T > &&rhs);

        bool empty() const;  //
        void clear();  //

        iter before_begin() noexcept;
        iter begin() noexcept;
        iter end() noexcept;

        constIter begin()  noexcept;//
        constIter cbegin() const noexcept;
        constIter end()  noexcept;//
        constIter cend() const noexcept;
        constIter cbefore_begin() const noexcept;

        iter insert_after(constIter pos, const T &value);  //
        iter insert_after(constIter pos, T &&value );   //
        iter insert_after(constIter pos, size_t count, const T &value );  //
        iter insert_after(constIter pos, iter first, iter last );  //
        //iter insert_after( const_iterator pos, std::initializer_list<T> ilist );

        iter erase_after(constIter pos);  //
        iter erase_after(constIter first, constIter last);  //

        template< typename ...Args >
        iterator emplace_after(const_iterator pos, Args &&...args);
        template< typename ...Args >
        void emplace_front(Args &&...args);

        void push_front(const T &value); //
        void push_front(T &&value); //
        void pop_front(); //

        void resize(size_t count);
        void resize(size_t count, const T& value);
        void swap(ForwardList< T >& other);
        void splice_after(constIter pos, ForwardList< T > &other);
        void splice_after(constIter pos, ForwardList< T > &&other);

        void remove(const T& value);
        void remove_if(T p);

        size_t size() const noexcept;

    private:
        List< T > *head_;
        size_t size_;
    };

    template< typename T>
    ForwardList< T >::ForwardList():
      head_(nullptr),
      size_(0)
    {}

    template< typename T >
    void ForwardList< T >::clear()
    {
        List< T > *node = head_;
        while(node != nullptr)
        {
            List< T > *tmp = node->next;
            delete node;
            node = tmp;
        }
        size_ = 0;
    }

    template< typename T >
    ForwardList< T >::~ForwardList():
    {
        clear();
        ::operator delete(head_);
    }

    template< typename T >
    size_t ForwardList< T >::size() const noexcept
    {
        return size;
    }
/*void push_front(const T &value);
        void push_front(T &&value);
        void pop_front();*/
    template< typename T>
    void ForwardList< T >::push_front(const T &value)
    {
        List< T > *node = new List< T >();
        node->data = value;
        node->next = head_;
        head_ = node;
        size_++:
    }

    template< typename T >
    void ForwardList< T >::push_front(T &&value)
    {
        push_front(value);
    }

    template< typename T >
    void ForwardList< T >::pop_front()
    {
        if (!head_)
        {
            return;
        }
        List< T > *tmp = head_->next;
        delete head_;
        head_ = tmp;
        size_--;
    }

    template< typename T >
    bool ForwardList< T >::empty() const
    {
        return head_ == nullptr;
    }
/* iter insert_after(constIter pos, const T &value);
        iter insert_after(constIter pos, T &&value );
        iter insert_after(constIter pos, size_t count, const T &value );
        iter insert_after(constIter pos, iter first, iter last );
        iter insert_after( constIter pos, std::initializer_list<T> ilist )
        */
    template< typename T >
    ForwardList< T >::iter ForwardList<T>::insert_after(constIter pos, const T &value)
    {
        List< T > *node = new List< T >();
        node->data = value;
        node->next = pos->next;
        pos->next = node;
        size_++;
        return pos->next;
    }

    template< typename  T >
    ForwardList< T >::iter ForwardList<T>::insert_after(constIter pos, T &&value )
    {
        return insert_after(pos, value);
    }

    template< typename  T >
    ForwardList< T >::iter ForwardList<T>::insert_after(constIter pos, size_t count, const T &value )
    {
        for (size_t i = 0; i < count; i++)
        {
            pos = insert_after(pos, value);
            pos++;
        }
        return pos;
    }

    template< typename  T >
    ForwardList< T >::iter ForwardList<T>::insert_after(constIter pos, iter first, iter last ):
    {
        while (first != last)
        {
            pos = insert_after(pos, *first);
            pos++;
            first++;
        }
        return pos;
    }
/*        iter erase_after(constIter pos);
        iter erase_after(constIter first, constIter last);*/
    template< typename  T >
    ForwardList< T >::iter ForwardList<T>::erase_after(constIter pos)
    {
        //чек проверку
        if (next = nullptr)
        {
            return nullptr;
        }
        List< T > *tmp = pos;
        tmp++;
        List< T > *tmp_next = tmp->next;
        delete tmp;
        pos->next = tmp_next;
        return pos;
    }

    template< typename  T >
    ForwardList< T >::iter ForwardList<T>::erase_after(constIter first, constIter last)
    {
        //вопрос сработает ли!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        size_t count = last - first;
        for (size_t i = 0; i < count; i++)
        {
            erase_after(first);
        }
        return last;
    }


    template< typename T >
    ForwardList< T >::ForwardList(const ForwardList< T > &lhs):
      ForwardList()
    {
      if (lhs.empty())
      {
        return;
      }
      insert_after(before_begin(), lhs.cbegin(), lhs.cend());
    }

}
#endif
