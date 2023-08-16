#ifndef QUICKSORT_H
#define QUICKSORT_H
#include <cstddef>
#include <algorithm>
//template< typename BidirectionalIterator, typename Compare >
//void quickSort(BidirectionalIterator begin, size_t size, Compare comp)
//{
//  if (size < 2)
//  {
//    return;
//  }
//  auto pivot = begin + size - 1;
//  auto i = begin;
//  for (auto j = begin; j < pivot; ++j)
//  {
//    if (comp(*j, *pivot))
//    {
//      std::swap(*i, *j);
//      ++i;
//    }
//  }
//  std::swap(*i, *pivot);
//  quickSort(begin, i - begin, comp);
//  quickSort(i + 1, pivot - i, comp);
//}
template< typename Iterator, typename Compare >
void quickSort(Iterator begin, size_t size, Compare comp)
{
  if (size < 2)
  {
    return;
  }
  auto pivot = begin;
  for (size_t i = 0; i < size - 1; ++i)
  {
    ++pivot;
  }
  size_t left_size = 0;
  for (Iterator i = begin; i != pivot; ++i)
  {
    if (comp(*i, *pivot))
    {
      left_size++;
    }
  }
  Iterator divider = begin;
  for (size_t i = 0; i < left_size; ++i)
  {
    ++divider;
  }
  std::iter_swap(pivot, divider);
  quickSort(begin, left_size, comp);
  Iterator right = divider;
  for (size_t i = 0; i < size - left_size - 1; ++i)
  {
    ++right;
  }
  quickSort(right, size - left_size - 1, comp);
}
#endif
