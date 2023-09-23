#include "huffman-tree.hpp"

#include <sort/merge.hpp>
#include "comporator.hpp"
#include "data-types.hpp"
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
    node_t * ins = new node_t {{it, count_encoding(phrase, it)}, nullptr, nullptr, nullptr, 0};
    if (list_.find(it) != list_.end())
    {
      delete ins;
      continue;
    }
    list_.insert(it, ins);
  }
  merge_sort(list_.begin(), list_.size(), SortByFreq());

  queue_t queue;
  for (auto it: list_)
  {
    queue.push(it.second);
  }

  while (queue.size() != 1)
  {
    node_t * left = queue.get();
    queue.pop();
    node_t * right = queue.get();
    queue.pop();

    std::size_t sum = left->data.second + left->data.second;
    queue.push(new node_t {{'\0', sum}, nullptr, left, right, 0});
  }
  root_ = queue.get();
  queue.pop();

  encode(root_, "");
  for (auto it: map_)
  {
    std::cout << "char: " << it.first << " code: " << it.second << "\n";
  }
}

turkin::HTree::~HTree()
{
  free(root_);
}

void turkin::HTree::encode(node_t * src, encoding_t code)
{
  if (src == nullptr)
  {
    return;
  }

  if (!src->left && !src->right)
  {
    if (map_.find(src->data.first) != map_.end())
    {
      map_[src->data.first] = code;
    }
    else
    {
      map_.insert(src->data.first, code);
    }
  }

  encode(src->left, code + "0");
  encode(src->right, code + "1");
}

void turkin::HTree::free(node_t * src)
{
  if (src == nullptr)
  {
    return;
  }
  free(src->left);
  free(src->right);
  delete src;
}
