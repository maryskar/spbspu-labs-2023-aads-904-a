#ifndef MURMURHASH2_H
#define MURMURHASH2_H
#include <string>
#include "wordentry.h"
struct HashTable
{
  explicit HashTable(size_t size);
  std::vector< WordEntry > data_;
  size_t capacity_;
  void print();
};
uint32_t generateMurmurHash2(const std::string &key, uint32_t m, int r);
#endif
