#include "filllist.hpp"
#include <random>
#include <forwardlist.hpp>

void hrushchev::fillRandomFloats(hrushchev::ForwardList< float >& list, size_t size)
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution< float > distribution(0, 10);

  for (size_t i = 0; i < size; ++i)
  {
    float random_float = distribution(gen);
    list.push_front(random_float);
  }
}

void hrushchev::fillRandomInts(hrushchev::ForwardList< int >& list, size_t size)
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution< int > distribution(0, 10);

  for (size_t i = 0; i < size; ++i)
  {
    int random_int = distribution(gen);
    list.push_front(random_int);
  }
}
