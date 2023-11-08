#ifndef HASH_H
#define HASH_H
#include <string>
#include <cstdint>
namespace fesenko
{
  uint32_t generate_jenkins_hash(const std::string key, uint32_t capacity);
}
#endif
