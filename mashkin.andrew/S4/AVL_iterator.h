#ifndef S4_AVL_ITERATOR_H
#define S4_AVL_ITERATOR_H
#include <functional>
#include <iterator>
#include <cassert>
#include <memory>
#include "const_AVL_iterator.h"
#include "tree.h"

namespace mashkin
{
  template< class T, class Comporator = std::less< T > >
  class AVL_iterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
  public:
    AVL_iterator();
    ~AVL_iterator() = default;
    AVL_iterator(const AVL_iterator< T, Comporator >&) = default;
    explicit AVL_iterator(Tree< T, Comporator >* rhs);

    AVL_iterator< T, Comporator >& operator=(const AVL_iterator< T, Comporator >&) = default;
    AVL_iterator< T, Comporator >& operator++();
    AVL_iterator< T, Comporator > operator++(int);
    AVL_iterator< T, Comporator >& operator--();
    AVL_iterator< T, Comporator > operator--(int);

    T& operator*();
    T* operator->();

    bool operator!=(const AVL_iterator< T >& rhs) const;
    bool operator==(const AVL_iterator< T >& rhs) const;

  private:
    template< class U, class C >
    friend class Const_AVL_iterator;
    Tree< T >* fake_;
    Tree< T >* node_;
    Comporator comp_;

    Tree< T >* getFake(Tree< T, Comporator >* rhs);
    void doParentForPlus();
    void doParentForMinus();
    void doWhileLeft();
    void doWhileRight();
  };

  template< class T, class Comporator >
  Tree< T >* AVL_iterator< T, Comporator >::getFake(Tree< T, Comporator >* rhs)
  {
    auto fake = rhs;
    while (fake != fake->parent_->parent_)
    {
      fake = fake->parent_;
    }
    fake = fake->parent_;
    return fake;
  }

  template< class T, class Comporator >
  bool AVL_iterator< T, Comporator >::operator==(const AVL_iterator< T >& rhs) const
  {
    return node_ == rhs.node_;
  }

  template< class T, class Comporator >
  bool AVL_iterator< T, Comporator >::operator!=(const AVL_iterator< T >& rhs) const
  {
    return !(rhs == *this);
  }

  template< class T, class Comporator >
  AVL_iterator< T, Comporator > AVL_iterator< T, Comporator >::operator--(int)
  {
    assert(node_ != nullptr);
    auto res(*this);
    --(*this);
    return res;
  }

  template< class T, class Comporator >
  T* AVL_iterator< T, Comporator >::operator->()
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data);
  }

  template< class T, class Comporator >
  T& AVL_iterator< T, Comporator >::operator*()
  {
    assert(node_ != nullptr);
    return node_->data;
  }

  template< class T, class Comporator >
  void AVL_iterator< T, Comporator >::doParentForMinus()
  {
    auto newNode = node_->parent_;
    while (newNode != fake_ && comp_(node_->data, newNode->data))
    {
      newNode = newNode->parent_;
    }
    if (newNode == fake_)
    {
      node_ = node_->left_;
    }
    else
    {
      node_ = newNode;
    }
  }

  template< class T, class Comporator >
  void AVL_iterator< T, Comporator >::doWhileRight()
  {
    auto newNode = node_->left_;
    while (newNode->right_)
    {
      newNode = newNode->right_;
    }
    node_ = newNode;
  }

  template< class T, class Comporator >
  AVL_iterator< T, Comporator >& AVL_iterator< T, Comporator >::operator--()
  {
    assert(node_ != nullptr);
    if (node_ == fake_)
    {
      node_ = node_->parent_;
      while (node_->right_)
      {
        node_ = node_->right_;
      }
    }
    else if (!node_->left_ && !node_->right_ && node_->parent_)
    {
      if (node_ == node_->parent_->left_)
      {
        doParentForMinus();
      }
      else
      {
        node_ = node_->parent_;
      }
    }
    else if (node_->left_ && node_->right_ && node_->parent_)
    {
      doWhileRight();
    }
    else if (node_->left_ && !node_->right_ && node_->parent_)
    {
      doWhileRight();
    }
    else if (!node_->parent_)
    {
      doWhileRight();
    }
    else if (!node_->left_ && node_->right_ && node_->parent_)
    {
      doParentForMinus();
    }
    return *this;
  }

  template< class T, class Comp >
  AVL_iterator< T, Comp > AVL_iterator< T, Comp >::operator++(int)
  {
    assert(node_ != nullptr);
    auto res(*this);
    ++(*this);
    return res;
  }

  template< class T, class Comp >
  void AVL_iterator< T, Comp >::doWhileLeft()
  {
    auto newNode = node_->right_;
    while (newNode->left_)
    {
      newNode = newNode->left_;
    }
    node_ = newNode;
  }

  template< class T, class Comp >
  void AVL_iterator< T, Comp >::doParentForPlus()
  {
    auto newNode = node_->parent_;
    while (newNode != fake_ && !comp_(node_->data, newNode->data))
    {
      newNode = newNode->parent_;
    }
    node_ = newNode;
  }

  template< class T, class Comp >
  AVL_iterator< T, Comp >& AVL_iterator< T, Comp >::operator++()
  {
    assert(node_ != nullptr);
    if (!node_->left_ && !node_->right_ && node_->parent_)
    {
      if (node_ == node_->parent_->left_)
      {
        node_ = node_->parent_;
      }
      else
      {
        doParentForPlus();
      }
    }
    else if (node_->left_ && node_->right_ && node_->parent_)
    {
      doWhileLeft();
    }
    else if (node_->left_ && !node_->right_ && node_->parent_)
    {
      doParentForPlus();
    }
    else if (!node_->parent_)
    {
      doWhileLeft();
    }
    else if (!node_->left_ && node_->right_ && node_->parent_)
    {
      doWhileLeft();
    }
    return *this;
  }

  template< class T, class Comp >
  AVL_iterator< T, Comp >::AVL_iterator():
    fake_(nullptr),
    node_(nullptr),
    comp_()
  {
  }

  template< class T, class Comp >
  AVL_iterator< T, Comp >::AVL_iterator(Tree< T, Comp >* rhs):
    fake_(getFake(rhs)),
    node_(rhs),
    comp_()
  {
  }
}
#endif
