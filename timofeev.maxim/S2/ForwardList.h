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
        using inter = ForwardListIter< T >;
        using constIter = ForwardListConstIter< T >;

        ForwardList();
        ~ForwardList();

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


    };
}
#endif
