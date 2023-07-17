#ifndef S4_AVL_H
#define S4_AVL_H
#include <functional>
#include "tree.h"
#include "AVL_iterator.h"
#include "const_AVL_iterator.h"

namespace mashkin
{
  template< class Key, class Value, class Comporator = std::less< Key > >
  class AVL
  {
  public:
    using v_type = std::pair< Key, Value >;
    using iter = AVL_iterator< v_type >;
    using const_iter = Const_AVL_iterator< v_type >;
    AVL();
    AVL(const AVL& lhs);
    AVL(AVL&& rhs);
    ~AVL();

    iter begin();
    iter end();
    const_iter cbegin();
    const_iter cend();

    iter insert(const v_type& val);
    iter insert(v_type&& val);
    template< class InputIter >
    iter insert(InputIter first, InputIter last);

    void clear();
    bool empty();

  private:
    void rotate_left(Tree< v_type >* node);
    void rotate_right(Tree< v_type >* node);
    void rotate_RightLeft(Tree< v_type >* node);
    void rotate_LeftRight(Tree< v_type >* node);
    size_t checkHeight(Tree< v_type >* head);
    size_t checkHeightImpl(Tree< v_type >* head, size_t height);
    Tree< v_type >* ins_impl(const v_type& data, Tree< v_type >* root, Tree< v_type >* before);
    void clear_impl(Tree< v_type >* toDel);
    Tree< v_type >* fake_;
    Comporator comp_;
  };

  template< class K, class V, class C >
  template< class InputIter >
  typename AVL< K, V, C >::iter AVL< K, V, C >::insert(InputIter first, InputIter last)
  {
    while (first != last)
    {
      insert(*first);
      first++;
    }
  }

  template< class K, class V, class C >
  typename AVL< K, V, C >::iter AVL< K, V, C >::insert(v_type&& val)
  {
    return insert(val);
  }

  template< class K, class V, class C >
  void AVL< K, V, C >::rotate_LeftRight(Tree< v_type >* node)
  {
    rotate_left(node->right_);
    rotate_right(node->parent_);
  }

  template< class K, class V, class C >
  void AVL< K, V, C >::rotate_RightLeft(Tree< v_type >* node)
  {
    rotate_right(node->left_);
    rotate_left(node->parent_);
  }

  template< class K, class V, class C >
  void AVL< K, V, C >::rotate_right(Tree< v_type >* node)
  {
    auto var = node->parent_;
    var->left_ = node->right_;
    if (var->left_)
    {
      var->left_->parent_ = var;
    }
    node->parent_ = var->parent_;
    node->right_ = var;
    if (var->parent_->left_ == var)
    {
      var->parent_->left_ = node;
    }
    else if (var->parent_->right_ == var)
    {
      var->parent_->right_ = node;
    }
    else
    {
      var->parent_->parent_ = node;
    }
    var->parent_ = node;
  }

  template< class K, class V, class C >
  void AVL< K, V, C >::rotate_left(Tree< v_type >* node)
  {
    auto var = node->parent_;
    var->right_ = node->left_;
    if (var->right_)
    {
      var->right_->parent_ = var;
    }
    node->parent_ = var->parent_;
    node->left_ = var;
    if (var->parent_->left_ == var)
    {
      var->parent_->left_ = node;
    }
    else if (var->parent_->right_ == var)
    {
      var->parent_->right_ = node;
    }
    else
    {
      var->parent_->parent_ = node;
    }
    var->parent_ = node;
  }

  template< class K, class V, class C >
  size_t AVL< K, V, C >::checkHeightImpl(Tree< v_type >* head, size_t height)
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

  template< class K, class V, class C >
  size_t AVL< K, V, C >::checkHeight(Tree< v_type >* head)
  {
    size_t height = 0;
    return checkHeightImpl(head, height);
  }

  template< class K, class V, class C >
  Tree< std::pair< K, V > >* AVL< K, V, C >::ins_impl(const v_type& data, Tree< v_type >* root, Tree< v_type >* before)
  {
    if (!root)
    {
      return before;
    }
    before = root;
    root = ins_impl(data, comp_(data.first, root->data.first) ? root->left_ : root->right_, before);
    return root;
  }

  template< class K, class V, class C >
  bool AVL< K, V, C >::empty()
  {
    return fake_ == fake_->parent_;
  }

  template< class K, class V, class C >
  typename AVL< K, V, C >::iter AVL< K, V, C >::insert(const v_type& val)
  {
    iter res;
    if (empty())
    {
      fake_->parent_ = new Tree< v_type >{val, fake_, nullptr, nullptr};
    }
    else
    {
      auto newNode = ins_impl(val, fake_->parent_, fake_->parent_);
      if (comp_(val.first, newNode->data.first))
      {
        newNode->left_ = new Tree< v_type >{val, newNode, nullptr, nullptr};
      }
      else
      {
        newNode->right_ = new Tree< v_type >{val, newNode, nullptr, nullptr};
      }
      res = iter(newNode);
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
          if (subRight <= subLeft)
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
    return res;
  }

  template< class K, class V, class C >
  typename AVL< K, V, C >::const_iter AVL< K, V, C >::cend()
  {
    return Const_AVL_iterator< v_type, C >(fake_);
  }

  template< class K, class V, class C >
  typename AVL< K, V, C >::const_iter AVL< K, V, C >::cbegin()
  {
    return Const_AVL_iterator< v_type, C >(fake_->parent_);
  }

  template< class K, class V, class C >
  typename AVL< K, V, C >::iter AVL< K, V, C >::end()
  {
    return AVL_iterator< v_type, C >(fake_);
  }

  template< class K, class V, class C >
  typename AVL< K, V, C >::iter AVL< K, V, C >::begin()
  {
    return AVL_iterator< v_type, C >(fake_->parent_);
  }

  template< class K, class V, class C >
  AVL< K, V, C >::~AVL()
  {
    clear();
    ::operator delete(fake_);
  }

  template< class K, class V, class C >
  void AVL< K, V, C >::clear_impl(Tree< v_type >* toDel)
  {
    if (!toDel)
    {
      return;
    }
    clear_impl(toDel->left_);
    clear_impl(toDel->right_);
    delete toDel;
  }

  template< class K, class V, class C >
  void AVL< K, V, C >::clear()
  {
    if (fake_ == fake_->parent_)
    {
      return;
    }
    clear_impl(fake_->parent_);
    fake_->parent_ = fake_;
  }

  template< class K, class V, class C >
  AVL< K, V, C >::AVL():
    fake_(static_cast< Tree< v_type >* >(::operator new(sizeof(Tree< v_type >)))),
    comp_()
  {
    fake_->left_ = nullptr;
    fake_->right_ = nullptr;
    fake_->parent_ = fake_;
  }
}
#endif
