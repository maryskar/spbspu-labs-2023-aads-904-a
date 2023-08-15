#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include "quicksort.h"
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
  std::random_device rd;
  std::mt19937 gen(rd());
  std::vector< int > dataInt(size);
  std::vector< float > dataFloat(size);
  if (dataType == "ints")
  {
    std::uniform_int_distribution< int > dist(1, 10);
    for (int i = 0; i < size; i++)
    {
      dataInt[i] = dist(gen);
    }
    if (sortOrder == "ascending")
    {
      quickSort(dataInt.begin(), dataInt.size(), std::less<>());
    }
    else
    {
      quickSort(dataInt.begin(), dataInt.size(), std::greater<>());
    }
    for (int x: dataInt)
    {
      std::cout << x << " ";
    }
  }
  else if (dataType == "floats")
  {
    std::uniform_real_distribution< float > dist(1.0, 10.0);
    for (int i = 0; i < size; i++)
    {
      dataFloat[i] = dist(gen);
    }
    if (sortOrder == "ascending")
    {
      quickSort(dataFloat.begin(), dataFloat.size(), std::less<>());
    }
    else
    {
      quickSort(dataFloat.begin(), dataFloat.size(), std::greater<>());
    }
    for (float x: dataFloat)
    {
      std::cout << x << " ";
    }
  }
  std::cout << "\n";
  return 0;
}