#ifndef TREE_H
#define TREE_H

#include <stdexcept>

namespace dmitriev
{
  template< typename T >
  struct Tree
  {
    T data;
    int height;

    Tree< T >* parent;
    Tree< T >* left;
    Tree< T >* right;
  };

  template< typename T >
  bool isEmpty(const Tree< T >* node) noexcept
  {
    return node == nullptr;
  }

  template< typename T >
  void clear(Tree< T >* root)
  {
    if (isEmpty(root))
    {
      return;
    }

    if (!isEmpty(root->left))
    {
      clear(root->left);
    }
    if (!isEmpty(root->right))
    {
      clear(root->right);
    }

    delete root;
  }

  template< typename T >
  Tree< T >* copy(Tree< T >* otherRoot)
  {
    if (isEmpty(otherRoot))
    {
      return nullptr;
    }

    Tree< T >* newNode = new Tree< T >{otherRoot->data, otherRoot->height, nullptr, nullptr, nullptr};

    try
    {
      newNode->left = copy(otherRoot->left);
    }
    catch (const std::exception&)
    {
      delete newNode;
      throw;
    }
    if (!isEmpty(newNode->left))
    {
      newNode->left->parent = newNode;
    }

    try
    {
      newNode->right = copy(otherRoot->right);
    }
    catch (const std::exception&)
    {
      clear(newNode->left);
      delete newNode;
      throw;
    }
    if (!isEmpty(newNode->right))
    {
      newNode->right->parent = newNode;
    }

    return newNode;
  }

}

#endif
