#include "hash.h"

uint32_t fesenko::generate_jenkins_hash(const std::string key)
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
  return hash;
}
