#ifndef MURMURHASH2_H
#define MURMURHASH2_H
#include <string>
namespace romanovich
{
  uint32_t generateMurmurHash2(const std::string &key, uint32_t m = 0x5bd1e995, int r = 24);
}
#endif
