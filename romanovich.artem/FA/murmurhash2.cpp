#include "murmurhash2.h"
namespace
{
  uint32_t projectHashToRange(uint32_t value, uint32_t maxValue)
  {
    uint64_t maxValue64 = static_cast< uint64_t >(maxValue);
    uint64_t result = static_cast< uint64_t >(value) * maxValue64;
    return static_cast< uint32_t >((result >> 32) + 1) - 1;
  }
}
uint32_t romanovich::generateMurmurHash2(const std::string &key, uint32_t maxValue, uint32_t m, int r)
{
  size_t len = key.length();
  uint32_t h = 0;
  const uint8_t *data = reinterpret_cast<const uint8_t *>(key.data());
  while (len >= 4)
  {
    uint32_t k = *(uint32_t *) data;
    k *= m;
    k ^= k >> r;
    k *= m;
    h *= m;
    h ^= k;
    data += 4;
    len -= 4;
  }
  if (len >= 3)
  {
    h ^= data[2] << 16;
  }
  if (len >= 2)
  {
    h ^= data[1] << 8;
  }
  if (len >= 1)
  {
    h ^= data[0];
    h *= m;
  }
  h ^= h >> 13;
  h *= m;
  h ^= h >> 15;
  return projectHashToRange(h, maxValue);
}
