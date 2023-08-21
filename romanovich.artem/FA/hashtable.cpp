#include <ostream>
#include <algorithm>
#include <iostream>
#include "hashtable.h"
#include "murmurhash2.h"
romanovich::HashTable::HashTable(size_t size, size_t capacity):
  size_(size),
  capacity_(capacity),
  data_(data_t(capacity))
{
}
void romanovich::HashTable::addKey(const std::string &key)
{
  uint32_t index = romanovich::generateMurmurHash2(key, capacity_);
  std::cerr << "Hash: " << index << "\n";
  if (data_[index].word.empty())
  {
    data_[index] = {key, {}};
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
    if (!entry.word.empty())
    {
      uint32_t newIndex = romanovich::generateMurmurHash2(entry.word, newCapacity);
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
    if (entry.word.empty())
    {
      continue;
    }
    out << "Index: " << i << ", Key: " << entry.word << ", Value: ";
    out << (entry.translations.empty() ? "EMPTY" : "size=" + std::to_string(entry.translations.size())) << "\n";
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
void romanovich::HashTable::addValue(const std::string &key, const std::string &trans)
{
  uint32_t index = romanovich::generateMurmurHash2(key, capacity_);
  if (data_[index].word.empty())
  {
    data_[index] = {key, {trans}};
  }
  else
  {
    data_[index].translations.push_back(trans);
    ++size_;
  }
  if (shouldResize())
  {
    resize(capacity_ * 2);
  }
}
void romanovich::HashTable::removeKey(const std::string &key)
{
  uint32_t index = romanovich::generateMurmurHash2(key, capacity_);
  if (data_[index].word != key)
  {
    return;
  }
  data_[index].translations.clear();
  data_[index].word.clear();
  --size_;
}
void romanovich::HashTable::removeValue(const std::string &word, const std::string &trans)
{
  uint32_t index = romanovich::generateMurmurHash2(word, capacity_);
  if (data_[index].word != word)
  {
    return;
  }
  auto &translations = data_[index].translations;
  translations.erase(
    std::remove(translations.begin(), translations.end(), trans),
    translations.end()
  );
}
size_t romanovich::HashTable::getSize() const
{
  return size_;
}
size_t romanovich::HashTable::getCapacity() const
{
  return capacity_;
}
const romanovich::HashTable::data_t &romanovich::HashTable::getData() const
{
  return data_;
}
WordEntry &romanovich::HashTable::operator[](const std::string &key)
{
  uint32_t index = romanovich::generateMurmurHash2(key, capacity_);
  return data_[index];
}
