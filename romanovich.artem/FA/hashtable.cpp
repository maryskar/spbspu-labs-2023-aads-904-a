#include <iostream>
#include "hashtable.h"
#include "murmurhash2.h"
HashTable::HashTable(size_t size, size_t capacity):
  size_(size),
  capacity_(capacity),
  data_(std::vector< WordEntry >(capacity))
{
}
void HashTable::print() const
{
  std::cout << "---Hash data---";
  std::cout << "Size: " << size_ << "\n";
  for (size_t i = 0; i < size_; ++i)
  {
    const WordEntry &entry = data_[i];
    if (entry.word.empty())
    {
      //continue;
    }
    std::cout << "Index: " << i << ", Key: " << entry.word << ", Value: " << entry.translations.size() << "\n";
  }
  std::cout << "---------------\n";
}
void HashTable::addWord(const std::string &word)
{
  uint32_t index = romanovich::generateMurmurHash2(word, capacity_);
  std::cerr << "Hash: " << index << "\n";
  if (data_[index].word.empty())
  {
    data_[index] = {word, {}};
    ++size_;
    if (shouldResize())
    {
      resize(capacity_ * 2);
    }
  }
}
HashTable::HashTable():
  size_(0),
  capacity_(10),
  data_(std::vector< WordEntry >(10))
{
}
bool HashTable::shouldResize() const
{
  double loadFactor = static_cast< double >(size_) / capacity_;
  return loadFactor > 0.7;
}
void HashTable::resize(size_t newCapacity)
{
  std::vector< WordEntry > newData(newCapacity);
  for (auto const &entry: data_)
  {
    if (!entry.word.empty())
    {
      uint32_t newIndex = romanovich::generateMurmurHash2(entry.word, newCapacity);
      newData[newIndex] = entry;
    }
  }
  capacity_ = newCapacity;
  data_ = std::move(newData);
}
