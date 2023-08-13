//
// Created by makst on 13.08.2023.
//

#ifndef SPBSPU_LABS_2023_AADS_904_A_FORWARDLIST_H
#define SPBSPU_LABS_2023_AADS_904_A_FORWARDLIST_H
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

        ForwardList(const ForwardList< T > &lhs);
        ForwardList(ForwardList< T > &&rhs) noexcept;
        ForwardList< T > &operator=(const ForwardList< T > &rhs);
        ForwardList< T > &operator=(ForwardList< T > &&rhs);

        bool empty() const;
        void clear();

        iter before_begin() noexcept;
        iter begin() noexcept;
        iter end() noexcept;

        constIter begin()  noexcept;//
        constIter cbegin() const noexcept;
        constIter end()  noexcept;//
        constIter cend() const noexcept;
        constIter cbefore_begin() const noexcept;

        iter insert_after(constIter pos, const T &value);
        iter insert_after(constIter pos, T &&value );
        iter insert_after(constIter pos, size_t count, const T &value );
        iter insert_after(constIter pos, iter first, iter last );

        iter erase_after(constIter pos);
        iter erase_after(constIter first, constIter last);

        template< typename ...Args >
        iterator emplace_after(const_iterator pos, Args &&...args);
        template< typename ...Args >
        void emplace_front(Args &&...args);

        void push_front(const T &value);
        void push_front(T &&value);
        void pop_front();


    };

}
#endif
