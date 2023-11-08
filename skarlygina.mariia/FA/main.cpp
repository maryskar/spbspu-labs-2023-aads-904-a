#include "hash_table.h"
#include <iostream>
int main()
{
  HashTable hash_table;
  hash_table.insertFromFile("text.txt");
  hash_table.insertFromFile("text1.txt"); //проверка передачи несуществующего файла

  hash_table.printWordFrequencies();

  size_t itemCount = hash_table.getNumberofItems();

  std::cout << "Number of items in the hash table: " << itemCount << std::endl;

  hash_table.printTopWords(3);

  return 0;
}
