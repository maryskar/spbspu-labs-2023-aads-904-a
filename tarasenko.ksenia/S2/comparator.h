#ifndef COMPARATOR_H
#define COMPARATOR_H
namespace tarasenko
{
  template< typename T>
  struct Comparator
  {
    bool operator()(const T& right_k, const T& left_k)
    {
      return right_k < left_k;
    }
  };
}
#endif
