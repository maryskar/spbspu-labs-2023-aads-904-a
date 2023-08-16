#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include "quicksort.h"
#include "shellsort.h"
#include "oddevensort.h"
#include "../common/forwardlist.h"
std::vector< int > generateRandomData(size_t size, int min, int max)
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::vector< int > data(size);
  std::uniform_int_distribution< int > dist(min, max);
  for (size_t i = 0; i < size; i++)
  {
    data[i] = dist(gen);
  }
  return data;
}
std::vector< float > generateRandomData(size_t size, float min, float max)
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::vector< float > data(size);
  std::uniform_real_distribution< float > dist(min, max);
  for (size_t i = 0; i < size; i++)
  {
    data[i] = dist(gen);
  }
  return data;
}
template< typename T >
void sortData(std::vector< T > &data, const std::string &sortOrder)
{
  if (sortOrder == "ascending")
  {
    oddEvenSort(data.begin(), data.size(), std::less<>());
  }
  else if (sortOrder == "descending")
  {
    quickSort(data.begin(), data.size(), std::greater<>());
  }
  else
  {
    throw std::invalid_argument("Invalid sort order.");
  }
}
template< typename T >
void lab(size_t size)
{
  std::vector< T > data = generateRandomData(size, 1, 10);
  romanovich::ForwardList< T > forwardList;
  for (size_t i = 0; i < size; ++i)
  {
    forwardList.push_front(data[i]);
  }
  print(forwardList.begin(), forwardList.end());
}
template< typename InputIt >
void printData(InputIt begin, InputIt end)
{
  for (auto it = begin; it != end; ++it)
  {
    if (it != begin)
    {
      std::cout << ' ';
    }
    std::cout << *it;
  }
}
int main(int argc, char *argv[])
{
  if (argc != 4)
  {
    std::cerr << "Invalid arguments number.\n";
    return 1;
  }
  size_t size = std::strtoull(argv[3], nullptr, 10);
  if (size == 0)
  {
    std::cerr << "Empty sequence.";
    return 2;
  }
  std::string sortOrder = argv[1];
  std::string dataType = argv[2];
  try
  {
    if (dataType == "ints")
    {
      std::vector< int > dataInt = generateRandomData(size, 1, 10);
      sortData(dataInt, sortOrder);
      printData(dataInt.begin(), dataInt.end());
    }
    else if (dataType == "floats")
    {
      std::vector< float > dataFloat = generateRandomData(size, 1.0f, 10.0f);
      sortData(dataFloat, sortOrder);
      printData(dataFloat.begin(), dataFloat.end());
    }
    else
    {
      std::cerr << "Invalid data type.";
      return 2;
    }
  }
  catch (...)
  {
    std::cerr << "Error while sorting ints.";
    return 2;
  }
  return 0;
}
