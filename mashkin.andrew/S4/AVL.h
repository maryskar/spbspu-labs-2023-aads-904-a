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
    void clear_impl(Tree< T, Comporator >* toDel);
    Tree< T, Comporator >* fake_;
    Comporator comp_;
  };

  template< class T, class C >
  bool AVL< T, C >::empty()
  {
    return fake_ == fake_->parent_;
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
    clear_impl(toDel->left);
    clear_impl(toDel->right);
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
    fake_->left = nullptr;
    fake_->right = nullptr;
    fake_->parent_ = fake_;
  }
}
#endif
