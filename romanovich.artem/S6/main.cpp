#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include "quicksort.h"
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
    quickSort(data.begin(), data.size(), std::less<>());
  }
  else
  {
    quickSort(data.begin(), data.size(), std::greater<>());
  }
}
template< typename T >
void printData(const std::vector< T > &data)
{
  for (const T &x: data)
  {
    std::cout << x << " ";
  }
  std::cout << "\n";
}
int main(int argc, char *argv[])
{
  if (argc != 4)
  {
    std::cerr << "Invalid arguments number.\n";
    return 1;
  }
  std::string sortOrder = argv[1];
  std::string dataType = argv[2];
  size_t size = std::strtoull(argv[3], nullptr, 10);
  if (dataType == "ints")
  {
    std::vector< int > dataInt = generateRandomData(size, 1, 10);
    sortData(dataInt, sortOrder);
    printData(dataInt);
  }
  else if (dataType == "floats")
  {
    std::vector< float > dataFloat = generateRandomData(size, 1.0f, 10.0f);
    sortData(dataFloat, sortOrder);
    printData(dataFloat);
  }
  return 0;
}
