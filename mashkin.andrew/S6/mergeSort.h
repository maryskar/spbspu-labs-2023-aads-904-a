#ifndef MASHKIN_ANDREW_MERGESORT_H
#define MASHKIN_ANDREW_MERGESORT_H
#include <cstddef>

namespace mashkin
{
  template< class InputStruct, class Comporator >
  void merge(InputStruct dataStruct, size_t left, size_t mid, size_t right, Comporator comp)
  {
    size_t subStructOne = mid - left + 1;
    size_t subStructTwo = right - mid;
    auto begin = dataStruct.begin();
    decltype(dataStruct) leftStruct(begin, begin + subStructOne);
    decltype(dataStruct) rightStruct(begin + subStructOne + 1, begin + right);
    size_t indOfSubStructOne = 0;
    size_t indOfSubStructTwo = 0;
    size_t indOfMergedStruct = left;
    auto leftBegin = leftStruct.begin();
    auto rightBegin = rightStruct.begin();
    while (indOfSubStructOne < subStructOne && indOfSubStructTwo < subStructTwo)
    {
      if (comp(*(leftBegin + indOfSubStructOne), *(rightBegin + indOfSubStructTwo)))
      {
        *(begin + indOfMergedStruct) = *(leftBegin + indOfSubStructOne);
        indOfSubStructOne++;
      }
      else
      {
        *(begin + indOfMergedStruct) = *(rightBegin + indOfSubStructTwo);
        indOfSubStructTwo++;
      }
      indOfMergedStruct++;
    }
    while (leftBegin + indOfSubStructOne != leftStruct.end())
    {
      *(begin + indOfMergedStruct) = *(leftBegin + indOfSubStructOne);
      indOfSubStructOne++;
      indOfMergedStruct++;
    }
    while (rightBegin + indOfSubStructTwo != rightStruct.end())
    {
      *(begin + indOfMergedStruct) = *(rightBegin + indOfSubStructTwo);
      indOfMergedStruct++;
      indOfSubStructTwo++;
    }
  }

  template< class InputIter, class Comporator >
  void mergeSort(InputIter dataStructIt, size_t begin, size_t end, Comporator comp)
  {
    if (begin <= end)
    {
      return;
    }
    size_t mid = begin + (end - begin) / 2;
    mergeSort< InputIter, Comporator >(dataStructIt, begin, mid, comp);
    mergeSort< InputIter, Comporator >(dataStructIt, mid + 1, end, comp);
    merge< InputIter, Comporator >(dataStructIt, begin, mid, end, comp);
  }
}
#endif
