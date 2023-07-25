#ifndef MASHKIN_ANDREW_QUICKSORT_H
#define MASHKIN_ANDREW_QUICKSORT_H
#include <cstddef>
#include <utility>

namespace mashkin
{
  template< class DataStrucct, class Type, class Comparator >
  int partition(DataStrucct& dataStrucct, int low, int high, Comparator comp)
  {
    Type pivot = dataStrucct[high];
    int i = (low - 1);
    for (auto j = low; j <= high - 1; j++)
    {
      if (comp(dataStrucct[j], pivot))
      {
        i++;
        std::swap(dataStrucct[i], dataStrucct[j]);
      }
    }
    std::swap(dataStrucct[i + 1], dataStrucct[high]);
    return (i + 1);
  }

  template< class DataStruct, class Type, class Comparator  >
  void quickSort(DataStruct& dataStruct, int low, int high, Comparator comp)
  {
    if (low < high)
    {
      int pivot = partition< DataStruct, Type, Comparator >(dataStruct, low, high, comp);
      quickSort< DataStruct, Type, Comparator >(dataStruct, low, pivot - 1, comp);
      quickSort< DataStruct, Type, Comparator >(dataStruct, pivot + 1, high, comp);
    }
  }
}
#endif
