#include <ostream>
#include <iostream>//
#include "hashtable.h"
#include "murmurhash2.h"
romanovich::HashTable::HashTable(size_t size, size_t capacity):
  size_(size),
  capacity_(capacity),
  data_(data_t(capacity))
{
}
void romanovich::HashTable::addWord(const std::string &word)
{
  uint32_t index = romanovich::generateMurmurHash2(word, capacity_);
  std::cerr << "Hash: " << index << "\n";
  if (data_[index].first.empty())
  {
    data_[index] = {word, {}};
    ++size_;
    if (shouldResize())
    {
      resize(capacity_ * 2);
    }
  }
}
romanovich::HashTable::HashTable():
  size_(0),
  capacity_(10),
  data_(data_t(10))
{
}
bool romanovich::HashTable::shouldResize() const
{
  double loadFactor = static_cast< double >(size_) / capacity_;
  return loadFactor > 0.7;
}
void romanovich::HashTable::resize(size_t newCapacity)
{
  data_t newData(newCapacity);
  for (auto const &entry: data_)
  {
    if (!entry.first.empty())
    {
      uint32_t newIndex = romanovich::generateMurmurHash2(entry.first, newCapacity);
      newData[newIndex] = entry;
    }
  }
  capacity_ = newCapacity;
  data_ = std::move(newData);
}
std::ostream &romanovich::HashTable::print(std::ostream &out) const
{
  out << "---Hash data---\n";
  out << "Size: " << size_ << "\n";
  for (size_t i = 0; i < capacity_; ++i)
  {
    const WordEntry &entry = data_[i];
    if (entry.first.empty())
    {
      continue;
    }
    out << "Index: " << i << ", Key: " << entry.first << ", Value: ";
    out << (entry.second.empty() ? "EMPTY" : "size=" + std::to_string(entry.second.size())) << "\n";
  }
  return out << "---------------\n";
}
romanovich::HashTable::HashTable(romanovich::HashTable &&other) noexcept:
  size_(other.size_),
  capacity_(other.capacity_),
  data_(std::move(other.data_))
{
}
romanovich::HashTable &romanovich::HashTable::operator=(const romanovich::HashTable &other)
{
  if (this != std::addressof(other))
  {
    size_ = other.size_;
    capacity_ = other.capacity_;
    data_ = other.data_;
  }
  return *this;
}
romanovich::HashTable &romanovich::HashTable::operator=(romanovich::HashTable &&other) noexcept
{
  if (this != std::addressof(other))
  {
    size_ = other.size_;
    capacity_ = other.capacity_;
    data_ = std::move(other.data_);
    other.size_ = 0;
    other.capacity_ = 0;
  }
  return *this;
}
