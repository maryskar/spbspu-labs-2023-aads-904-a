#include "murmurhash2.h"
uint32_t generateMurmurHash2(const std::string &key, uint32_t m, int r)
{
  size_t len = key.length();
  uint32_t h = 0;
  //
  const uint8_t *data = reinterpret_cast<const uint8_t *>(key.data());
  //
  while (len >= 4)
  {
    uint32_t k = *(uint32_t *) data;
    //
    k *= m;
    k ^= k >> r;
    k *= m;
    //
    h *= m;
    h ^= k;
    //
    data += 4;
    len -= 4;
  }
  //
  switch (len)
  {
    case 3:
      h ^= data[2] << 16;
    case 2:
      h ^= data[1] << 8;
    case 1:
      h ^= data[0];
      h *= m;
    default:
    {
    }
  }
  //
  h ^= h >> 13;
  h *= m;
  h ^= h >> 15;
  //
  return h;
}