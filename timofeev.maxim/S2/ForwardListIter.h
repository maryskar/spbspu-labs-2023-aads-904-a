#ifndef FORWARDLISTITER_H
#define FORWARDLISTITER_H
#include <List.h>
namespace timofeev
{
  template<typename T>
  class ForwardListIterator
  {
    friend class ForwardList<T>;

  public:
    ForwardListIterator();
    ~ForwardListIterator() = default;

    ForwardListIterator(timofeev::List<T> *other);
    ForwardListIterator(const ForwardListConstIterator <T> &other) noexcept;

    bool operator!=(ForwardListIterator<T> &other) const
    bool operator==(ForwardListIterator<T> &other) const

    T &operator*();
    T *operator->();

    ForwardListIterator<T> &operator++();
    ForwardListIterator<T> operator++(int);

    /* ForwardListIterator (TElement *start) noexcept
     bool 	operator!= (ForwardListIterator other) const
     TElement & 	operator* () const
     ForwardListIterator & 	operator++ ()
     ForwardListIterator 	operator++ (int)
     TElement * 	operator-> () const
     bool 	operator== (ForwardListIterator other) const*/

  private:
    timofeev::List<T> *node_;
  };
}
  template< typename T>
  timofeev::ForwardListIterator< T >::ForwardListIterator():
    node_(nullptr)
  {}

  template< typename T >
  timofeev::ForwardListIterator< T >::ForwardListIterator(timofeev::List< T >* other);
  {
    node = other;
  }

#endif //SPBSPU_LABS_2023_AADS_904_A_FORWARDLISTITER_H
