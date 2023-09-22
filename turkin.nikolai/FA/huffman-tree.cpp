#include "huffman-tree.hpp"

#include <sort/merge.hpp>
#include "comporator.hpp"

#include <iostream>

namespace
{
  std::size_t count_encoding(const phrase_t & phrase, char del)
  {
    std::size_t amount = 0;
    for (char it: phrase)
    {
      if (it == del)
      {
        amount++;
      }
    }
    return amount;
  }
}

turkin::HTree::HTree(const phrase_t & phrase):
  root_(nullptr),
  list_()
{
  for (char it: phrase)
  {
    list_.push_front(std::make_pair(it, count_encoding(phrase, it)));
  }
  merge_sort(list_.begin(), list_.size(), SortByFreq());
  for (auto it: list_)
  {
    std::cout << "char: " << it.first << " freq: " << it.second << "\n";
  }
}
