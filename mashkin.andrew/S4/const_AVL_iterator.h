#ifndef S4_CONST_AVL_ITERATOR_H
#define S4_CONST_AVL_ITERATOR_H
#include <cassert>
#include <functional>
#include <iterator>
#include <memory>
#include "AVL_iterator.h"
#include "tree.h"

namespace mashkin
{
  template< class T, class C >
  class AVL_iterator;

  template< class T, class Comp = std::less< T > >
  class Const_AVL_iterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
  public:
    Const_AVL_iterator();
    ~Const_AVL_iterator() = default;
    Const_AVL_iterator(const Const_AVL_iterator< T, Comp >&) = default;
    Const_AVL_iterator(const AVL_iterator< T, Comp >& rhs);
    explicit Const_AVL_iterator(Tree< T, Comp >* rhs);

    Const_AVL_iterator< T, Comp >& operator=(const Const_AVL_iterator< T, Comp >&) = default;
    Const_AVL_iterator< T, Comp >& operator++();
    Const_AVL_iterator< T, Comp > operator++(int);
    Const_AVL_iterator< T, Comp >& operator--();
    Const_AVL_iterator< T, Comp > operator--(int);

    const T& operator*() const;
    const T* operator->() const;

    bool operator!=(const Const_AVL_iterator< T >& rhs) const;
    bool operator==(const Const_AVL_iterator< T >& rhs) const;

  private:
    Tree< T >* node_;
    Comp comp_;

    void doParentForPlus();
    void doParentForMinus();
    void doWhileLeft();
    void doWhileRight();
  };

  template< class T, class Comp >
  Const_AVL_iterator< T, Comp >::Const_AVL_iterator(const AVL_iterator< T, Comp >& rhs):
    node_(rhs.node_),
    comp_(rhs.comp_)
  {
  }

  template< class T, class Comp >
  Const_AVL_iterator< T, Comp >::Const_AVL_iterator():
    node_(nullptr),
    comp_()
  {
  }

  template< class T, class Comp >
  void Const_AVL_iterator< T, Comp >::doWhileRight()
  {
    auto newNode = node_->left;
    while (newNode->right)
    {
      newNode = newNode->right;
    }
    node_ = newNode;
  }

  template< class T, class Comp >
  void Const_AVL_iterator< T, Comp >::doWhileLeft()
  {
    auto newNode = node_->right;
    while (newNode->left)
    {
      newNode = newNode->left;
    }
    node_ = newNode;
  }

  template< class T, class Comp >
  void Const_AVL_iterator< T, Comp >::doParentForMinus()
  {
    auto newNode = node_->parent_;
    while (newNode && comp_(node_->data, newNode->data))
    {
      newNode = newNode->parent_;
    }
    node_ = newNode;
  }

  template< class T, class Comp >
  void Const_AVL_iterator< T, Comp >::doParentForPlus()
  {
    auto newNode = node_->parent_;
    while (newNode && !comp_(node_->data, newNode->data))
    {
      newNode = newNode->parent_;
    }
    node_ = newNode;
  }

  template< class T, class Comp >
  bool Const_AVL_iterator< T, Comp >::operator!=(const Const_AVL_iterator< T >& rhs) const
  {
    return !(rhs == *this);
  }

  template< class T, class Comp >
  bool Const_AVL_iterator< T, Comp >::operator==(const Const_AVL_iterator< T >& rhs) const
  {
    return node_ == rhs.node_;
  }

  template< class T, class Comp >
  const T* Const_AVL_iterator< T, Comp >::operator->() const
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data);
  }

  template< class T, class Comp >
  const T& Const_AVL_iterator< T, Comp >::operator*() const
  {
    assert(node_ != nullptr);
    return node_->data;
  }

  template< class T, class Comp >
  Const_AVL_iterator< T, Comp > Const_AVL_iterator< T, Comp >::operator--(int)
  {
    assert(node_ != nullptr);
    auto res(*this);
    --(*this);
    return res;
  }

  template< class T, class Comp >
  Const_AVL_iterator< T, Comp >& Const_AVL_iterator< T, Comp >::operator--()
  {
    assert(node_ != nullptr);
    if (!node_->left && !node_->right && node_->parent_)
    {
      if (node_ == node_->parent_->left)
      {
        doParentForMinus();
      }
      else
      {
        node_ = node_->parent_;
      }
    }
    else if (node_->left && node_->right && node_->parent_)
    {
      doWhileRight();
    }
    else if (node_->left && !node_->right && node_->parent_)
    {
      doWhileRight();
    }
    else if (!node_->parent_)
    {
      doWhileRight();
    }
    else if (!node_->left && node_->right && node_->parent_)
    {
      doParentForMinus();
    }
    return *this;
  }

  template< class T, class Comp >
  Const_AVL_iterator< T, Comp > Const_AVL_iterator< T, Comp >::operator++(int)
  {
    assert(node_ != nullptr);
    auto res(*this);
    ++(*this);
    return res;
  }

  template< class T, class Comp >
  Const_AVL_iterator< T, Comp >& Const_AVL_iterator< T, Comp >::operator++()
  {
    assert(node_ != nullptr);
    if (!node_->left && !node_->right && node_->parent_)
    {
      if (node_ == node_->parent_->left)
      {
        node_ = node_->parent_;
      }
      else
      {
        doParentForPlus();
      }
    }
    else if (node_->left && node_->right && node_->parent_)
    {
      doWhileLeft();
    }
    else if (node_->left && !node_->right && node_->parent_)
    {
      doParentForPlus();
    }
    else if (!node_->parent_)
    {
      doWhileLeft();
    }
    else if (!node_->left && node_->right && node_->parent_)
    {
      doWhileLeft();
    }
    return *this;
  }

  template< class T, class Comp >
  Const_AVL_iterator< T, Comp >::Const_AVL_iterator(Tree< T, Comp >* rhs):
    node_(rhs),
    comp_()
  {
  }
}
#endif
