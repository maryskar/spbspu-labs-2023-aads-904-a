#ifndef FORWARDLISTITER_H
#define FORWARDLISTITER_H

namespace timofeev
{
  template< typename T >
  class ForwardListIterator
  {
    friend class ForwardList< T >;
  public:
    ForwardListIterator();
    ~ForwardListIterator() = default;


   /* ForwardListIterator (TElement *start) noexcept
    bool 	operator!= (ForwardListIterator other) const
    TElement & 	operator* () const
    ForwardListIterator & 	operator++ ()
    ForwardListIterator 	operator++ (int)
    TElement * 	operator-> () const
    bool 	operator== (ForwardListIterator other) const*/
  };
}
#endif //SPBSPU_LABS_2023_AADS_904_A_FORWARDLISTITER_H
