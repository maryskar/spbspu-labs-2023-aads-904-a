#include "hash_table.h"
#include "linked_list.h"
#include <vector>
#include <fstream>

size_t HashTable::hash(std::string key)
{
  size_t value = 0;
  for (int i = 0; i < key.length(); i++)
  {
    value += key[i];
  }

  return (key.length() * value) % length;
}

HashTable::HashTable(size_t tableLength)
{
  if (tableLength <= 0)
  {
    tableLength = 10;
  }

  arr = new LinkedList[tableLength];
  length = tableLength;
}

HashTable::~HashTable()
{
  delete[] arr;
}

void HashTable::insert(Node* key)
{
  std::string lowercaseKey = key->key_;

  lowercaseKey.erase(std::remove_if(lowercaseKey.begin(), lowercaseKey.end(), [](char c) {return !std::isalpha(c);}), lowercaseKey.end());
  std::transform(lowercaseKey.begin(), lowercaseKey.end(), lowercaseKey.begin(), [](char c) {return std::tolower(c);});

  if (!lowercaseKey.empty())
  {
    size_t index = hash(lowercaseKey);
    Node* existingNode = arr[index].getItem(lowercaseKey);

    if (existingNode)
    {
      existingNode->frequency_++;
      delete key;
    }
    else
    {
      arr[index].insert(key);
    }
  }
}

bool HashTable::remove(std::string key)
{
  size_t index = hash(key);
  return arr[index].remove(key);
}

Node* HashTable::getItemByKey(std::string key)
{
  size_t index = hash(key);
  return arr[index].getItem(key);
}

size_t HashTable::getLength()
{
  return length;
}

size_t HashTable::getNumberofItems()
{
  size_t itemCount = 0;
  for (int i = 0; i < length; i++)
    itemCount += arr[i].getLength();
  return itemCount;
}

void HashTable::insertFromFile(const std::string filename)
{
  std::ifstream inputFile(filename);
  if (inputFile.is_open())
  {
    std::string word;
    while (inputFile >> word)
    {
      if (std::all_of(word.begin(), word.end(), ::isalpha))
      {
        Node* node = new Node{word, 0};
        insert(node);
      }
    }
    inputFile.close();
  }
  else
  {
    std::cout << "Unable to open file: " << filename << std::endl;
  }
}

void HashTable::printWordFrequencies()
{

  std::cout << "Word Frequencies:\n";
  for (int i = 0; i < length; i++)
  {
    Node* current = arr[i].getHead();
    while (current != nullptr)
    {
      if (current->frequency_ != 0)
      {
        std::cout << "Word: " << current->key_ << ", Frequency: " << current->frequency_ << std::endl;
      }

      current = current->next;
    }
  }
}

void HashTable::printTopWords(size_t n)
{
  std::cout << "\nTop " << n << " Words by Frequency:\n";

  std::vector<std::pair<std::string, size_t>> wordFreqs;
  for (int i = 0; i < length; i++)
  {
    Node* current = arr[i].getHead();
    while (current != nullptr)
    {
      wordFreqs.push_back(std::make_pair(current->key_, current->frequency_));
      current = current->next;
    }
  }

  std::sort(wordFreqs.begin(), wordFreqs.end(),
    [](const std::pair<std::string, int>& a, const std::pair<std::string, size_t>& b)
    {
      return a.second > b.second;
    });

  size_t count = 0;
  for (const auto& pair : wordFreqs)
  {
    std::cout << "Word: " << pair.first << ", Frequency: " << pair.second << std::endl;
    count++;
    if (count == n)
      break;
  }
}
