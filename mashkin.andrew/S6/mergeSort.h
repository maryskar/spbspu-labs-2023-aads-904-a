#ifndef MASHKIN_ANDREW_MERGESORT_H
#define MASHKIN_ANDREW_MERGESORT_H
#include <cstddef>
#include <iterator>

namespace mashkin
{
  template< class InputStruct, class Comporator >
  void merge(InputStruct& dataStruct, size_t left, size_t mid, size_t right, Comporator comp)
  {
    size_t subStructOne = mid - left + 1;
    size_t subStructTwo = right - mid;
    auto begin = dataStruct.begin();
    auto varBegin = begin;
    auto varEnd = begin;
    std::advance(varBegin, left);
    std::advance(varEnd, left + subStructOne);
    std::remove_reference_t< decltype(dataStruct) > leftStruct(varBegin, varEnd);
    varEnd = begin;
    varBegin = begin;
    std::advance(varBegin, left + subStructOne);
    std::advance(varEnd, mid + 1 + subStructTwo);
    std::remove_reference_t< decltype(dataStruct) > rightStruct(varBegin, varEnd);
    size_t indOfMergedStruct = left;
    auto iter = begin;
    std::advance(iter, indOfMergedStruct);
    auto leftIter = leftStruct.begin();
    auto rightIter = rightStruct.begin();
    while (leftIter != leftStruct.end() && rightIter != rightStruct.end())
    {
      if (comp(*leftIter, *rightIter))
      {
        *iter = *leftIter;
        leftIter++;
      }
      else
      {
        *iter = *rightIter;
        rightIter++;
      }
      iter++;
    }
    while (leftIter != leftStruct.end())
    {
      *iter = *leftIter;
      leftIter++;
      iter++;
    }
    while (rightIter != rightStruct.end())
    {
      *iter = *rightIter;
      rightIter++;
      iter++;
    }
  }

  template< class InputStruct, class Comporator >
  void mergeSort(InputStruct& dataStructIt, size_t begin, size_t end, Comporator comp)
  {
    if (begin >= end)
    {
      return;
    }
    size_t mid = begin + (end - begin) / 2;
    mergeSort< InputStruct, Comporator >(dataStructIt, begin, mid, comp);
    mergeSort< InputStruct, Comporator >(dataStructIt, mid + 1, end, comp);
    merge< InputStruct, Comporator >(dataStructIt, begin, mid, end, comp);
  }
}
#endif
