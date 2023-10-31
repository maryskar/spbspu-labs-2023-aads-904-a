#include "hash.h"

uint32_t makeHashInCapacity(uint32_t hash, uint32_t capacity)
{
  uint64_t capacity64 = static_cast< uint64_t >(capacity);
  uint64_t result = static_cast< uint64_t >(hash) * capacity64;
  return static_cast< uint32_t >((result >> 32) + 1) - 1;
}

uint32_t fesenko::generate_jenkins_hash(const std::string key, uint32_t capacity)
{
  size_t len = key.size();
  uint32_t hash = 0;
  for(size_t i = 0; i < len; ++i) {
    hash += key[i];
    hash += (hash << 10);
    hash ^= (hash >> 6);
  }
  hash += (hash << 3);
  hash ^= (hash >> 11);
  hash += (hash << 15);
  return makeHashInCapacity(hash, capacity);
}
