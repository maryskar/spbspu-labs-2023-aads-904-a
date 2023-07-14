#ifndef S4_AVL_ITERATOR_H
#define S4_AVL_ITERATOR_H
#include <functional>
#include <iterator>
#include <cassert>
#include "tree.h"

namespace mashkin
{
  template< class T, class Comporator = std::less< T > >
  class AVL_iterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
  public:
    AVL_iterator();
    ~AVL_iterator() = default;
    explicit AVL_iterator(const AVL_iterator< T >&);
    explicit AVL_iterator(Tree< T >* rhs);

    AVL_iterator< T >& operator=(const AVL_iterator< T >&);
    AVL_iterator< T >& operator++();
    AVL_iterator< T > operator++(int);
    AVL_iterator< T >& operator--();
    AVL_iterator< T > operator--(int);

    T& operator*();
    T* operator->();

    bool operator!=(const AVL_iterator< T >& rhs) const;
    bool operator==(const AVL_iterator< T >& rhs) const;

  private:
    Tree< T >* node_;
    Comporator comp_;
    void doWhileParent();
    void doWhileLeft();
  };

  template< class T, class Comp >
  AVL_iterator< T >& AVL_iterator< T, Comp >::operator--()
  {
    return ;
  }

  template< class T, class Comp >
  AVL_iterator< T > AVL_iterator< T, Comp >::operator++(int)
  {
    assert(node_ != nullptr);
    auto res(*this);
    ++(*this);
    return res;
  }

  template< class T, class Comp >
  void AVL_iterator< T, Comp >::doWhileLeft()
  {
    auto newNode = node_->right;
    while (newNode->left)
    {
      newNode = newNode->left;
    }
    node_ = newNode;
  }

  template< class T, class Comp >
  void AVL_iterator< T, Comp >::doWhileParent()
  {
    auto newNode = node_->parent_;
    while (newNode && !comp_(node_->data, newNode->data))
    {
      newNode = newNode->parent_;
    }
    node_ = newNode;
  }

  template< class T, class Comp >
  AVL_iterator< T >& AVL_iterator< T, Comp >::operator++()
  {
    assert(node_ != nullptr);
    if (!node_->left && !node_->right && node_->parent_)
    {
      if (node_ == node_->parent_->left)
      {
        node_ = node_->parent_;
        return *this;
      }
      else
      {
        doWhileParent();
        return *this;
      }
    }
    else if (node_->left && node_->right && node_->parent_)
    {
      doWhileLeft();
      return *this;
    }
    else if (!node_->right && node_->parent_)
    {
      doWhileParent();
      return *this;
    }
    else if (!node_->parent_)
    {
      doWhileLeft();
      return *this;
    }
    else if (!node_->left && node_->right && node_->parent_)
    {
      doWhileLeft();
      return *this;
    }
    return *this;
  }

  template< class T, class Comp >
  AVL_iterator< T, Comp >::AVL_iterator():
    node_(nullptr),
    comp_()
  {
  }

  template< class T, class Comp >
  AVL_iterator< T, Comp >::AVL_iterator(Tree< T >* rhs):
    node_(rhs),
    comp_()
  {
  }
}
#endif
