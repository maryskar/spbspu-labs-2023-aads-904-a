#ifndef S4_AVL_H
#define S4_AVL_H
#include <functional>
#include "tree.h"
#include "AVL_iterator.h"
#include "const_AVL_iterator.h"

namespace mashkin
{
  template< class T, class Comporator = std::less< T > >
  class AVL
  {
  public:
    using iter = AVL_iterator< T, Comporator >;
    using const_iter = Const_AVL_iterator< T, Comporator >;
    AVL();
    AVL(const AVL& lhs);
    AVL(AVL&& rhs);
    ~AVL();

    iter begin();
    iter end();
    const_iter cbegin();
    const_iter cend();

    iter insert(const T& val);
    iter insert(T&& val);
    template< class InputIter >
    iter insert(InputIter first, InputIter last);

    void clear();
    bool empty();

  private:
    void rotate_left(Tree< T, Comporator >* node);
    void rotate_right(Tree< T, Comporator >* node);
    void rotate_RightLeft(Tree< T, Comporator >* node);
    void rotate_LeftRight(Tree< T, Comporator >* node);
    size_t checkHeight(Tree< T, Comporator >* head);
    size_t checkHeightImpl(Tree< T, Comporator >* head, size_t height);
    Tree< T, Comporator >* insert_impl(const T& data, Tree< T, Comporator >* root, Tree< T, Comporator >* before);
    void clear_impl(Tree< T, Comporator >* toDel);
    Tree< T, Comporator >* fake_;
    Comporator comp_;
  };

  template< class T, class C >
  size_t AVL< T, C >::checkHeightImpl(Tree< T, C >* head, size_t height)
  {
    if (!head)
    {
      return height;
    }
    height++;
    size_t left = checkHeightImpl(head->left_, height);
    size_t right = checkHeightImpl(head->right_, height);
    height = left < right ? right : left;
    return height;
  }

  template< class T, class C >
  size_t AVL< T, C >::checkHeight(Tree< T, C >* head)
  {
    size_t height = 0;
    return checkHeightImpl(head, height);
  }

  template< class T, class C >
  Tree< T, C >* AVL< T, C >::insert_impl(const T& data, Tree< T, C >* root, Tree< T, C >* before)
  {
    if (!root)
    {
      return before;
    }
    before = root;
    root = insert_impl(data, comp_(data, root->data) ? root->left_ : root->right_, before);
    return root;
  }

  template< class T, class C >
  bool AVL< T, C >::empty()
  {
    return fake_ == fake_->parent_;
  }

  template< class T, class C >
  AVL< T, C >::iter AVL< T, C >::insert(const T& val)
  {
    if (empty())
    {
      fake_->parent_ = new Tree< T, C >{val, fake_, nullptr, nullptr};
    }
    else
    {
      auto newNode = insert_impl(val, fake_->parent, fake_->parent);
      if (comp_(val, newNode->data))
      {
        newNode->left_ = new Tree< T, C >{val, newNode, nullptr, nullptr};
      }
      else
      {
        newNode->right_ = new Tree< T, C >{val, newNode, nullptr, nullptr};
      }
      while (newNode != fake_)
      {
        size_t left = checkHeight(newNode->left_);
        size_t right = checkHeight(newNode->right_);
        if (right - left == 2)
        {
          auto subTree = newNode->right_;
          auto subLeft = checkHeight(subTree->left_);
          auto subRight = checkHeight(subTree->right_);
          if (subLeft <= subRight)
          {
            rotate_left(subTree);
          }
          else
          {
            rotate_RightLeft(subTree);
          }
        }
        else if (left - right == 2)
        {
          auto subTree = newNode->left_;
          auto subLeft = checkHeight(subTree->left_);
          auto subRight = checkHeight(subTree->right_);
          if (subLeft <= subRight)
          {
            rotate_right(subTree);
          }
          else
          {
            rotate_LeftRight(subTree);
          }
        }
        newNode = newNode->parent_;
      }
    }
  }

  template< class T, class Comp >
  AVL< T, Comp >::const_iter AVL< T, Comp >::cend()
  {
    return Const_AVL_iterator< T, Comp >(fake_);
  }

  template< class T, class Comp >
  AVL< T, Comp >::const_iter AVL< T, Comp >::cbegin()
  {
    return Const_AVL_iterator< T, Comp >(fake_->parent_);
  }

  template< class T, class Comporator >
  AVL< T, Comporator >::iter AVL< T, Comporator >::end()
  {
    return AVL_iterator< T, Comporator >(fake_);
  }

  template< class T, class Comporator >
  AVL< T, Comporator >::iter AVL< T, Comporator >::begin()
  {
    return AVL_iterator< T, Comporator >(fake_->parent_);
  }

  template< class T, class Comporator >
  AVL< T, Comporator >::~AVL()
  {
    clear();
    ::operator delete(fake_);
  }

  template< class T, class Comporator >
  void AVL< T, Comporator >::clear_impl(Tree< T, Comporator >* toDel)
  {
    if (!toDel)
    {
      return;
    }
    clear_impl(toDel->left_);
    clear_impl(toDel->right_);
    delete toDel;
  }

  template< class T, class Comporator >
  void AVL< T, Comporator >::clear()
  {
    if (fake_ == fake_->parent_)
    {
      return;
    }
    clear_impl(fake_->parent_);
    fake_->parent_ = fake_;
  }

  template< class T, class Comp >
  AVL< T, Comp >::AVL():
    fake_(static_cast< Tree< T, Comp >* >(::operator new(sizeof(Tree< T, Comp >)))),
    comp_()
  {
    fake_->left_ = nullptr;
    fake_->right_ = nullptr;
    fake_->parent_ = fake_;
  }
}
#endif
