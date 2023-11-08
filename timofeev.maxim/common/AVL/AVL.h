#ifndef SPBSPU_LABS_2023_AADS_904_A_AVL_H
#define SPBSPU_LABS_2023_AADS_904_A_AVL_H
#include <functional>
#include <iterator>
#include <memory>
#include "AVLiter.h"
#include "Trees/Tree.h"
namespace timofeev
{
  template< typename Key, typename Value, typename Compare = std::less<> >
  class AVL
  {
    template< typename K, typename V, typename C >
    friend class AVLConstIter;
    template< typename K, typename V, typename C >
    friend class AVLIterator;
  public:
    using pairType = std::pair< Key, Value >;
    using tree = Tree< pairType >;
    using iter = AVLIterator< Key, Value, Compare >;
    using constIter = AVLConstIter< Key, Value, Compare >;

    AVL();
    AVL(const AVL& rhs);
    AVL(AVL&& rhs) noexcept;
    ~AVL();

    AVL& operator=(const AVL& rhs);
    AVL& operator=(AVL&& rhs);

    iter begin();
    constIter begin() const;
    iter end();
    constIter end() const;
    constIter cbegin() const ;
    constIter cend() const;

    Value& at(const Key& key);
    const Value& at(const Key& key) const;
    Value& operator[](const Key& key);

    iter insert(const pairType& val);
    iter insert(pairType&& val);
    template< class InputIter >
    iter insert(InputIter first, InputIter last);

    iter erase(iter pos);
    iter erase(constIter pos);
    iter erase(constIter first, constIter last);

    void clear() noexcept;
    size_t size() const noexcept;
    bool empty() const noexcept;
    iter find(const Key& key);
    constIter find(const Key& key) const;

    size_t count(const Key& key) const;
    void swap(AVL &rhs);
    bool contains(const Key& key) const;
    void push(const Key& key, const Value& value);
  private:
    tree* root_;
    Compare comp_;
    size_t size_;
    tree* balance(tree* node);
    tree* recurIns(tree* node, const pairType &val);
    size_t getBF(tree* node);
    tree* rotateRight(tree* node);
    tree* rotateLeft(tree* node);
    void updHeight(tree* node) noexcept;
    size_t getHeight(const tree* node) const noexcept;
    tree* getMax(tree* node) const noexcept;
    tree* getMin(tree* node) const noexcept;
    void copyTree(const AVL& node);
    void free(tree* node);
  };

  template< typename Key, typename Value, typename Compare >
  void AVL< Key, Value, Compare >::swap(AVL & rhs)
  {
    std::swap(root_, rhs.root_);
    std::swap(comp_, rhs.comp_);
    size_ = rhs.size_;
  }
  template< typename Key, typename Value, typename Compare >
  void AVL< Key, Value, Compare >::push(const Key& key, const Value& value)
  {
    insert(std::make_pair(key, value));
  }

  template< typename Key, typename Value, typename Compare >
  template< class InputIter >
  typename AVL< Key, Value, Compare >::iter AVL< Key, Value, Compare >::insert(InputIter first, InputIter last)
  {
    while (first != last)
    {
      insert(*first);
      first++;
    }
    return iter(last);
  }

  template< typename Key, typename Value, typename Compare >
  typename AVL< Key, Value, Compare >::iter AVL< Key, Value, Compare >::insert(pairType &&val)
  {
    return insert(static_cast< const pairType& >(val));
  }

  template< typename Key, typename Value, typename Compare >
  typename AVL< Key, Value, Compare >::iter AVL< Key, Value, Compare >::erase(constIter first, constIter last)
  {
    while (first != last)
    {
      erase(*first);
      first++;
    }
    return iter(last);
  }

  template< typename Key, typename Value, typename Compare >
  typename AVL< Key, Value, Compare >::iter AVL< Key, Value, Compare >::erase(constIter pos)
  {
    tree* delNode = pos.node_;
    tree* tmp = nullptr;
    if (!delNode->left_ || !delNode->right_)
    {
      tmp = (delNode->left_) ? delNode->left_ : delNode->right_;
      if (!tmp)
      {
        tmp = delNode;
      }
      else
      {
        *delNode = *tmp;
      }
    }
    else
    {
      tmp = getMin(delNode->right_);
      if (tmp->parent_ != delNode)
      {
        delNode->right_ = tmp->right_;
        tmp->right_ = delNode->right_;
      }
      if (delNode->parent_ == nullptr)
      {
        root_ = tmp;
      }
      else if (delNode == delNode->parent_->left_)
      {
        delNode->parent_->left_ = tmp;
      }
      else
      {
        delNode->parent_->right_ = tmp;
      }
      tmp->left_ = delNode->left_;
      tmp->right_ = delNode->right_;
    }
    if (tmp != delNode)
    {
      delete delNode;
      balance(tmp);
    }
    size_--;
    return iter(tmp);
  }

  template< typename Key, typename Value, typename Compare >
  typename AVL< Key, Value, Compare >::iter AVL< Key, Value, Compare >::erase(iter pos)
  {
    return erase(static_cast< constIter >(pos));
  }

  template< typename Key, typename Value, typename Compare >
  void AVL< Key, Value, Compare >::free(tree* node)
  {
    if (node == nullptr)
    {
      return;
    }
    if (node->left_)
    {
      free(node->left_);
      node->left_ = nullptr;
    }
    if (node->right_)
    {
      free(node->right_);
      node->right_ = nullptr;
    }
    delete node;
  }

  template< typename Key, typename Value, typename Compare >
  AVL< Key, Value, Compare > &AVL< Key, Value, Compare >::operator=(AVL &&rhs)
  {
    clear();
    swap(rhs);
    return *this;
  }

  template< typename Key, typename Value, typename Compare >
  void AVL< Key, Value, Compare >::copyTree(const AVL &node)
  {
    for(auto it = node.cbegin(); it != node.cend(); ++it)
    {
      insert(*it);
    }
  }

  template< typename Key, typename Value, typename Compare >
  AVL< Key, Value, Compare > &AVL< Key, Value, Compare >::operator=(const AVL &rhs)
  {
    clear();
    copyTree(rhs);
    return *this;
  }

  template< typename Key, typename Value, typename Compare >
  AVL< Key, Value, Compare >::AVL(AVL &&rhs) noexcept:
    root_(rhs.root_),
    comp_(rhs.comp_),
    size_(rhs.size_)
  {
    rhs.root_ = nullptr;
    rhs.size_ = 0;
  }

  template< typename Key, typename Value, typename Compare >
  AVL< Key, Value, Compare >::AVL(const AVL& rhs):
    root_(nullptr),
    comp_(rhs.comp_),
    size_(rhs.size_)
  {
    copyTree(rhs);
  }

  template< typename Key, typename Value, typename Compare >
  size_t AVL< Key, Value, Compare >::count(const Key &key) const
  {
    auto it = find(key);
    return (it != end()) ? 1ull : 0ull;
  }

  template< typename Key, typename Value, typename Compare >
  Value &AVL< Key, Value, Compare >::operator[](const Key &key)
  {
    auto it = find(key);
    if (it == end())
    {
      it = insert({key, Value()});
    }
    return it->second;
  }

  template< typename Key, typename Value, typename Compare >
  const Value &AVL< Key, Value, Compare >::at(const Key &key) const
  {
    constIter it = find(key);
    if (it == end())
    {
      throw std::invalid_argument("invalid_argument");
    }
    return it->second;
  }

  template< typename Key, typename Value, typename Compare >
  Value &AVL< Key, Value, Compare >::at(const Key &key)
  {
    iter it = find(key);
    if (it == end())
    {
      throw std::invalid_argument("invalid_argument");
    }
    return it->second;
  }

  template< typename Key, typename Value, typename Compare >
  AVL< Key, Value, Compare >::AVL():
    root_(nullptr),
    comp_(),
    size_(0)
  {}

  template< typename Key, typename Value, typename Compare >
  typename AVL< Key, Value, Compare >::constIter
      AVL< Key, Value, Compare >::find(const Key &key) const
  {
    iter result = const_cast< AVL * >(this)->find(key);
    return constIter(result.node_);
  }

  template< typename Key, typename Value, typename Compare >
  typename AVL< Key, Value, Compare >::iter AVL< Key, Value, Compare >::find(const Key &key)
  {
    tree* cur = root_;
    while (cur != nullptr)
    {
      if (!(comp_(key, cur->data.first) || comp_(cur->data.first, key)))
      {
        return iter(cur);
      }
      else if (comp_(key, cur->data.first))
      {
        cur = cur->left_;
      }
      else
      {
        cur = cur->right_;
      }
    }
    return end();
  }

  template< typename Key, typename Value, typename Compare >
  bool AVL< Key, Value, Compare >::contains(const Key &key) const
  {
    return find(key) != end();
  }

  template< typename Key, typename Value, typename Compare >
  AVL< Key, Value, Compare >::~AVL()
  {
    clear();
  }

  template< typename Key, typename Value, typename Compare >
  typename AVL< Key, Value, Compare >::iter
      AVL< Key, Value, Compare >::insert(const pairType &val)
  {
    root_ = recurIns(root_, val);
    return find(val.first);
  }

  template< typename Key, typename Value, typename Compare >
  typename AVL< Key, Value, Compare >::tree*
      AVL< Key, Value, Compare >::recurIns(tree* node, const pairType &val)
  {
    if (node == nullptr)
    {
      node = new tree{val, nullptr, nullptr, nullptr, 1};
      size_++;
    }
    else
    {
      if (comp_(val.first, node->data.first))
      {
        node->left_ = recurIns(node->left_, val);
        if (node->left_ != nullptr)
        {
          node->left_->parent_ = node;
        }
      }
      else if (comp_(node->data.first, val.first))
      {
        node->right_ = recurIns(node->right_, val);
        if (node->right_ != nullptr)
        {
          node->right_->parent_ = node;
        }
      }
      else
      {
        node->data.second = val.second;
      }
    }
    return balance(node);
  }

  template< typename Key, typename Value, typename Compare >
  typename AVL< Key, Value, Compare >::tree
      *AVL< Key, Value, Compare >::rotateLeft(tree *node)
  {
    if (node == nullptr)
    {
      return nullptr;
    }
    tree *newRoot = node->right_;
    if (newRoot == nullptr)
    {
      return node;
    }
    node->right_ = newRoot->left_;
    if (node->right_ != nullptr)
    {
      node->right_->parent_ = node;
    }
    newRoot->parent_ = node->parent_;
    if (node->parent_ == nullptr)
    {
      root_ = newRoot;
    }
    else
    {
      if (node == node->parent_->left_)
      {
        node->parent_->left_ = newRoot;
      }
      else
      {
        node->parent_->right_ = newRoot;
      }
    }
    newRoot->left_ = node;
    node->parent_ = newRoot;
    updHeight(node);
    updHeight(newRoot);
    return newRoot;
  }

  template< typename Key, typename Value, typename Compare >
  typename AVL< Key, Value, Compare >::tree *AVL< Key, Value, Compare >::rotateRight(tree *node)
  {
    if (node == nullptr)
    {
      return nullptr;
    }
    tree *newRoot = node->left_;
    if (newRoot == nullptr)
    {
      return node;
    }
    node->left_ = newRoot->right_;
    if (node->left_ != nullptr)
    {
      node->left_->parent_ = node;
    }
    newRoot->parent_ = node->parent_;
    if (node->parent_ == nullptr)
    {
      root_ = newRoot;
    }
    else if (node == node->parent_->left_)
    {
      node->parent_->left_ = newRoot;
    }
    else
    {
      node->parent_->right_ = newRoot;
    }
    newRoot->right_ = node;
    node->parent_ = newRoot;
    updHeight(node);
    updHeight(newRoot);
    return newRoot;
  }

  template< typename Key, typename Value, typename Compare >
  size_t AVL< Key, Value, Compare >::getBF(tree *node)
  {
    int leftHeight = (node->left_ != nullptr) ? node->left_->height : 0;
    int rightHeight = (node->right_ != nullptr) ? node->right_->height : 0;
    return leftHeight - rightHeight;
  }

  template< typename Key, typename Value, typename Compare >
  typename AVL< Key, Value, Compare >::tree *AVL< Key, Value, Compare >::balance(tree *node)
  {
    updHeight(node);
    int flag = getBF(node);
    if (flag > 1)
    {
      if (getBF(node->left_) < 0)
      {
        node->left_ = rotateLeft(node->left_);
      }
      return rotateRight(node);
    }
    else if (flag < -1)
    {
      if (getBF(node->right_) > 0)
      {
        node->right_ = rotateRight(node->right_);
      }
      return rotateLeft(node);
    }
    return node;
  }

  template< typename Key, typename Value, typename Compare >
  void AVL< Key, Value, Compare >::updHeight(tree *node) noexcept
  {
    node->height = std::max(getHeight(node->left_), getHeight(node->right_)) + 1;
  }

  template< typename Key, typename Value, typename Compare >
  size_t AVL< Key, Value, Compare >::getHeight(const tree *node) const noexcept
  {
    return (node == nullptr) ? 0 : node->height;
  }

  template< typename Key, typename Value, typename Compare >
  typename AVL< Key, Value, Compare >::tree
      *AVL< Key, Value, Compare >::getMin(tree *node) const noexcept
  {
    if (!node)
    {
      return nullptr;
    }
    while (node->left_)
    {
      node = node->left_;
    }
    return node;
  }

  template< typename Key, typename Value, typename Compare >
  typename AVL< Key, Value, Compare >::tree
      *AVL< Key, Value, Compare >::getMax(tree *node) const noexcept
  {
    if (!node)
    {
      return nullptr;
    }
    while (node->right_)
    {
      node = node->right_;
    }
    return node;
  }

  template< typename Key, typename Value, typename Compare >
  bool AVL< Key, Value, Compare >::empty() const noexcept
  {
    return root_ == nullptr;
  }

  template< typename Key, typename Value, typename Compare >
  size_t AVL< Key, Value, Compare >::size() const noexcept
  {
    return size_;
  }

  template< typename Key, typename Value, typename Compare >
  void AVL< Key, Value, Compare >::clear() noexcept
  {
    free(root_);
    root_ = nullptr;
  }

  template< typename Key, typename Value, typename Compare >
  typename AVL< Key, Value, Compare >::constIter AVL< Key, Value, Compare >::cbegin() const
  {
    return constIter(getMin(root_));
  }

  template< typename Key, typename Value, typename Compare >
  typename AVL< Key, Value, Compare >::constIter AVL< Key, Value, Compare >::end() const
  {
    return cend();
  }

  template< typename Key, typename Value, typename Compare >
  typename AVL< Key, Value, Compare >::constIter AVL< Key, Value, Compare >::cend() const
  {
    return constIter(nullptr);
  }

  template< typename Key, typename Value, typename Compare >
  typename AVL< Key, Value, Compare >::iter AVL< Key, Value, Compare >::end()
  {
    return iter(nullptr);
  }

  template< typename Key, typename Value, typename Compare >
  typename AVL< Key, Value, Compare >::constIter AVL< Key, Value, Compare >::begin() const
  {
    return cbegin();
  }

  template< typename Key, typename Value, typename Compare >
  typename AVL< Key, Value, Compare >::iter AVL< Key, Value, Compare >::begin()
  {
    tree* tmp = getMin(root_);
    return iter(tmp);
  }

}
#endif
