#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <algorithm>
#include <string>
#include "linked_list.h"
class HashTable
{
private:
  LinkedList* arr;
  size_t length;
  size_t hash(std::string key);

public:
  HashTable(size_t tableLength = 10);
  ~HashTable();

  void insert(Node* key);
  bool remove(std::string key);
  Node* getItemByKey(std::string key);
  size_t getLength();
  size_t getNumberofItems();
  void insertFromFile(const std::string filename);
  void printWordFrequencies();
  void printTopWords(size_t n);
};
#endif
