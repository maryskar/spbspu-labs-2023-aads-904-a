#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <cstddef>
#include <vector>
#include "wordentry.h"
class HashTable
{
public:
  HashTable();
  explicit HashTable(size_t size, size_t capacity = 100);
  void addWord(const std::string &word);
  //сделать круче
  void print() const;
  void resize(size_t newCapacity);
private:
  size_t size_;
  size_t capacity_;
  std::vector< WordEntry > data_;
  bool shouldResize() const;
};
#endif
