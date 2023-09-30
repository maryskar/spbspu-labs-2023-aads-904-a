#ifndef RANDOMDATAGENERATOR_H
#define RANDOMDATAGENERATOR_H
#include <vector>
#include <cstddef>
namespace romanovich
{
  std::vector< int > generateRandomInts(size_t size, int min, int max);
  std::vector< float > generateRandomFloats(size_t size, float min, float max);
}
#endif
