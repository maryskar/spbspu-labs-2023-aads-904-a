#ifndef FILLDEQUERANDOM_H
#define FILLDEQUERANDOM_H

#include <random>
#include <deque>

namespace dmitriev
{
  template< typename T >
  std::deque< T > fiillDequeRandom(size_t count)
  {
    std::random_device rd;
    std::mt19937 mt(rd());

    std::deque< T >  newData;

    if (std::is_same< T, int >::value)
    {
      std::uniform_int_distribution< int > dist(0, 1000);
      for (size_t i = 0; i < count; i++)
      {
        newData.push_back(dist(mt));
      }
    }
    else if (std::is_same< T, float >::value)
    {
      std::uniform_real_distribution< float > dist(0.0, 1000.0);
      for (size_t i = 0; i < count; i++)
      {
        newData.push_back(dist(mt));
      }
    }
    //else
    //{
    //  throw std::invalid_argument("incorrect data type");
    //}


    return newData;
  }
}

#endif
