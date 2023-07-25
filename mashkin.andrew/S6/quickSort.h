#ifndef MASHKIN_ANDREW_QUICKSORT_H
#define MASHKIN_ANDREW_QUICKSORT_H
#include <cstddef>
#include <utility>

namespace mashkin
{
  template< class DataStrucct >
  int partition(DataStrucct& dataStrucct, int low, int high)
  {
    int pivot = dataStrucct[high];
    int i = (low - 1);
    for (auto j = low; j <= high - 1; j++)
    {
      if (dataStrucct[j] < pivot)
      {
        i++;
        std::swap(dataStrucct[i], dataStrucct[j]);
      }
    }
    std::swap(dataStrucct[i + 1], dataStrucct[high]);
    return (i + 1);
  }

  template< class DataStruct >
  void quickSort(DataStruct& dataStruct, int low, int high)
  {
    if (low < high)
    {
      int pivot = partition(dataStruct, low, high);
      quickSort(dataStruct, low, pivot - 1);
      quickSort(dataStruct, pivot + 1, high);
    }
  }
}
#endif
