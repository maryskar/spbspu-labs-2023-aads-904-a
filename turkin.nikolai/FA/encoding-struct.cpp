#include "encoding-struct.hpp"

#include <iostream>

#include "comporator.hpp"
#include "data-types.hpp"

#include <sort/merge.hpp>

namespace
{
  std::size_t count_encoding(const turkin::phrase_t & phrase, char del)
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

turkin::HType::HType():
  root_(nullptr),
  list_(),
  map_()
{}

turkin::HType::HType(const phrase_t & phrase):
  root_(nullptr),
  list_(),
  map_()
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
}

turkin::HType::HType(const HType & htree):
  root_(copy(htree.root_)),
  list_(htree.list_),
  map_(htree.map_)
{}

turkin::HType::HType(HType && htree):
  root_(htree.root_),
  list_(htree.list_),
  map_(htree.map_)
{
  htree.root_ = nullptr;
  htree.list_.clear();
  htree.map_.clear();
}

turkin::HType & turkin::HType::operator=(const HType & htree)
{
  if (std::addressof(htree) == this)
  {
    return * this;
  }
  root_ = copy(htree.root_);
  list_ = htree.list_;
  map_ = htree.map_;
  return * this;
}

turkin::HType & turkin::HType::operator=(HType && htree)
{
  if (std::addressof(htree) == this)
  {
    return * this;
  }
  root_ = htree.root_;
  list_ = htree.list_;
  map_ = htree.map_;
  htree.root_ = nullptr;
  htree.list_.clear();
  htree.map_.clear();
  return * this;
}

turkin::HType::~HType()
{
  free(root_);
}

const turkin::encoding_list_t & turkin::HType::get_encoding_list()
{
  return list_;
}

const turkin::encoding_map_t & turkin::HType::get_encoding_map()
{
  return map_;
}

void turkin::HType::encode(node_t * src, encoding_t code)
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

void turkin::HType::free(node_t * src)
{
  if (src == nullptr)
  {
    return;
  }
  free(src->left);
  free(src->right);
  delete src;
}

turkin::node_t * turkin::HType::copy(node_t * src)
{
  node_t * new_root;
  if (src == nullptr)
  {
    return nullptr;
  }
  new_root = new node_t {src->data, nullptr, nullptr, nullptr, 0};
  new_root->left = copy(src->left);
  new_root->right = copy(src->right);
  return new_root;
}

std::ostream & turkin::operator<<(std::ostream & out, const encoding_map_t & map)
{
  for (auto it = map.begin(); it != map.end(); it++)
  {
    out << "| " << it->first << " - " << it->second << " ";
  }
  out << "|";
  return out;
}
