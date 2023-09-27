#ifndef MASHKIN_ANDREW_MERGESORT_H
#define MASHKIN_ANDREW_MERGESORT_H
#include <cstddef>
#include <iterator>
#include <ForwardList/forwardList.h>

namespace mashkin
{
  template< class Iter, class Comp >
  void merge(Iter first, Iter mid, Iter last, Comp comp)
  {
    ForwardList< std::remove_reference_t< decltype(*first) > > temp(first, last);
    Iter leftIt = first;
    Iter rightIt = mid;
    auto tempIt = temp.begin();
    while (leftIt != mid && rightIt != last)
    {
      if (comp(*leftIt, *rightIt))
      {
        *tempIt++ = *leftIt++;
      }
      else
      {
        *tempIt++ = *rightIt++;
      }
    }
    while (leftIt != mid)
    {
      *tempIt++ = *leftIt++;
    }
    while (rightIt != last)
    {
      *tempIt++ = *rightIt++;
    }
    tempIt = temp.begin();
    for (Iter it = first; it != last; ++it)
    {
      *it = *tempIt++;
    }
  }

  template< class Iter, class Comp >
  void mergeSort(Iter first, Iter last, Comp comp)
  {
    size_t size = std::distance(first, last);
    if (size <= 1)
    {
      return;
    }
    Iter mid = first;
    std::advance(mid, size / 2);
    mergeSort(first, mid, comp);
    mergeSort(mid, last, comp);
    merge(first, mid, last, comp);
  }

//  template< class InputStruct, class Comporator >
//  void merge(InputStruct& dataStruct, size_t left, size_t mid, size_t right, Comporator comp)
//  {
//    size_t subStructOne = mid - left + 1;
//    size_t subStructTwo = right - mid;
//    auto begin = dataStruct.begin();
//    auto varBegin = begin;
//    auto varEnd = begin;
//    std::advance(varBegin, left);
//    std::advance(varEnd, left + subStructOne);
//    std::remove_reference_t< decltype(dataStruct) > leftStruct(varBegin, varEnd);
//    varEnd = begin;
//    varBegin = begin;
//    std::advance(varBegin, left + subStructOne);
//    std::advance(varEnd, mid + 1 + subStructTwo);
//    std::remove_reference_t< decltype(dataStruct) > rightStruct(varBegin, varEnd);
//    size_t indOfMergedStruct = left;
//    auto iter = begin;
//    std::advance(iter, indOfMergedStruct);
//    auto leftIter = leftStruct.begin();
//    auto rightIter = rightStruct.begin();
//    while (leftIter != leftStruct.end() && rightIter != rightStruct.end())
//    {
//      if (comp(*leftIter, *rightIter))
//      {
//        *iter = *leftIter;
//        leftIter++;
//      }
//      else
//      {
//        *iter = *rightIter;
//        rightIter++;
//      }
//      iter++;
//    }
//    while (leftIter != leftStruct.end())
//    {
//      *iter = *leftIter;
//      leftIter++;
//      iter++;
//    }
//    while (rightIter != rightStruct.end())
//    {
//      *iter = *rightIter;
//      rightIter++;
//      iter++;
//    }
//  }
//
//  template< class InputStruct, class Comporator >
//  void mergeSort(InputStruct& dataStructIt, size_t begin, size_t end, Comporator comp)
//  {
//    if (begin >= end)
//    {
//      return;
//    }
//    size_t mid = begin + (end - begin) / 2;
//    mergeSort< InputStruct, Comporator >(dataStructIt, begin, mid, comp);
//    mergeSort< InputStruct, Comporator >(dataStructIt, mid + 1, end, comp);
//    merge< InputStruct, Comporator >(dataStructIt, begin, mid, end, comp);
//  }
}
#endif
