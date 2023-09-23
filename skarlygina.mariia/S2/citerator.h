#ifndef CITERATOR_H
#define CITERATOR_H
#include "list.h"

template < typename T >
class CIterator : public std::iterator< std::forward_iterator_tag, T >
{
public:
  bool operator ==(const CIterator&) const;
  bool operator!=(const CIterator&) const;
  CIterator& operator++();
  CIterator operator++(int);
  const T& operator*() const;
  const T* operator->() const;
private:
  const List< T >* ptr_;
  explicit CIterator(const List< T >*);
};

#endif
