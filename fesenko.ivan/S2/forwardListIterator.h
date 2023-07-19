#ifndef FORWARDLISTITERATOR_H
#define FORWARDLISTITERATOR_H
namespace fesenko
{
  template< typename T >
  class ForwardListIterator
  {
   public:
    using this_t = ForwardListIterator< T >;
    ForwardListIterator();
    ForwardListIterator(const this_t &);
    ForwardListIterator(this_t &&);
    ~ForwardListIterator();
    this_t &operator=(const this_t &);
    this_t &operator=(this_t &&);
    this_t &operator++();
    this_t &operator++(int);
    T &operator*();
    const T &operator*() const;
    T *operator->();
    const T *operator->() const;
    bool operator!=(const this_t &) const;
    bool operator==(const this_t &) const;
   private:
    List< T > *node;
  }
}
#endif
