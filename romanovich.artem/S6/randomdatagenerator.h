#ifndef RANDOMDATAGENERATOR_H
#define RANDOMDATAGENERATOR_H
#include <vector>
#include <cstddef>
namespace romanovich
{
  std::vector< int > generateRandomData(size_t size, int min, int max);
  std::vector< float > generateRandomData(size_t size, float min, float max);
}
#endif
