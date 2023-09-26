#ifndef FORWARDITERATOR_H
#define FORWARDITERATOR_H
namespace aksenov
{
  template< typename T >
  class ForwardIterator
  {
  public:
    ForwardIterator();
    ~ForwardIterator() = default;
    ForwardIterator(listT< T > *node);
    ForwardIterator(const ForwardIterator< T > &) = default;

    ForwardIterator< T > &operator=(const ForwardIterator< T > &rhs) = default;

    ForwardIterator< T > &operator++();
    ForwardIterator< T > &operator++(int);

    T &operator*();
    T *operator->();

    bool operator!=(const ForwardIterator< T > &rhs) const;
    bool operator==(const ForwardIterator< T > &rhs) const;
  private:
    listT< T > *node_;
  };

}
#endif
