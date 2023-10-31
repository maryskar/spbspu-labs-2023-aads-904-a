#ifndef HASHTABLE_T
#define HASHTABLE_H
#include <vector>
#include <string>
namespace fesenko
{
  class HashTable
  {
   public:
    using data_t = std::vector< std::string >;
    HashTable();
    HashTable(const HashTable &other);
    HashTable(HashTable &&other);
    HashTable &operator=(const HashTable &other);
    HashTable &operator=(HashTable &&other);
    ~HashTable();
   private:
    size_t size_;
    size_t capacity_;
    data_t data_;
  };
}
#endif
