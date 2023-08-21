#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <cstddef>
#include <vector>
#include "../S2/dict.h"
#include "wordentry.h"
namespace romanovich
{
  class HashTable
  {
  public:
    //using data_t = std::vector< Dictionary< std::string, std::string > >;
    using data_t = std::vector< WordEntry >;
    HashTable();
    explicit HashTable(size_t size, size_t capacity = 100);
    void addWord(const std::string &word);
    std::ostream &print(std::ostream &out) const;
    void resize(size_t newCapacity);
  private:
    size_t size_;
    size_t capacity_;
    data_t data_;
    std::vector< Dictionary<std::string, std::string> > dicts_;
    bool shouldResize() const;
  };
}
#endif
