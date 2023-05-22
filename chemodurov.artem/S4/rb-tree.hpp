#ifndef S4_RB_TREE_HPP
#define S4_RB_TREE_HPP
#include "rotatable-binary-search-tree.hpp"
#include "const-rb-iterator.hpp"

namespace chemodurov
{
  template< typename T, typename Compare = std::less< > >
  class RBTree
  {
   public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using value_compare = Compare;
    using reference = value_type &;
    using const_reference = const value_type &;
    using iterator = typename RotatableBinarySearchTree< value_type, value_compare >::iterator;
    using const_iterator = typename RotatableBinarySearchTree< value_type, value_compare >::const_iterator;
    using this_t = RBTree< value_type, value_compare >;
    RBTree();
    RBTree(const this_t & other) = default;
    RBTree(this_t && other) noexcept;
    explicit RBTree(const value_compare & comp);
    template< typename InputIt >
    RBTree(InputIt first, InputIt last, const value_compare & comp = value_compare());
    RBTree(std::initializer_list< value_type > init, const value_compare & comp = value_compare());
    ~RBTree() = default;
    this_t & operator=(const this_t & other);
    this_t & operator=(this_t && other) noexcept;
    this_t & operator=(std::initializer_list< value_type > init);
    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;
    bool empty() const noexcept;
    size_t size() const noexcept;
    void clear() noexcept;
    std::pair< iterator, bool > insert(const_reference value);
    template< typename P >
    std::pair< iterator, bool > insert(P && value);
    iterator insert(const_iterator pos, const_reference value);
    template< typename P >
    iterator insert(const_iterator pos, P && value);
    template< typename InputIt >
    void insert(InputIt first, InputIt last);
    void insert(std::initializer_list< value_type > init);
    template< typename... Args >
    std::pair< iterator, bool > emplace(Args && ... args);
    template< typename... Args >
    iterator emplace_hint(const_iterator hint, Args && ... args);
    reference at(const_reference value);
    const_reference at(const_reference value) const;
    reference operator[](const_reference value);
    reference operator[](value_type && value);
    iterator erase(iterator pos);
    iterator erase(const_iterator pos);
    iterator erase(const_iterator first, const_iterator last);
    size_type erase(const_reference value);
    void swap(this_t & other);
    size_type count(const_reference value) const;
    iterator find(const_reference value);
    const_iterator find(const_reference value) const;
    std::pair< iterator, iterator > equal_range(const_reference value);
    std::pair< const_iterator, const_iterator > equal_range(const_reference value) const;
    iterator lower_bound(const_reference value);
    const_iterator lower_bound(const_reference value) const;
    iterator upper_bound(const_reference value);
    const_iterator upper_bound(const_reference value) const;
    value_compare value_comp() const;
   private:
    RotatableBinarySearchTree< T, Compare > data_;
    void balanceTreeAfterInsert(Tree< T, Compare > * inserted);
    void balanceTreeErase(Tree< T, Compare > * todel);
  };

  template< typename T, typename Compare >
  RBTree< T, Compare >::RBTree():
   data_()
  {
    data_.data_.fake_->color_ = 'b';
  }

  template< typename T, typename Compare >
  RBTree< T, Compare >::RBTree(this_t && other) noexcept:
   data_(std::move(other.data))
  {
    data_.data_.fake_->color_ = 'b';
  }

  template< typename T, typename Compare >
  RBTree< T, Compare >::RBTree(const value_compare & comp):
   data_(comp)
  {
    data_.data_.fake_->color_ = 'b';
  }

  template< typename T, typename Compare >
  template< typename InputIt >
  RBTree< T, Compare >::RBTree(InputIt first, InputIt last, const value_compare & comp):
   RBTree(comp)
  {
    insert(first, last);
  }

  template< typename T, typename Compare >
  RBTree< T, Compare >::RBTree(std::initializer_list< value_type > init, const value_compare & comp):
   RBTree(init.begin(), init.end(), comp)
  {}

  template< typename T, typename Compare >
  RBTree< T, Compare > & RBTree< T, Compare >::operator=(const this_t & other)
  {
    data_ = other.data;
    return *this;
  }

  template< typename T, typename Compare >
  RBTree< T, Compare > & RBTree< T, Compare >::operator=(this_t && other) noexcept
  {
    data_ = std::move(other.data);
    return *this;
  }

  template< typename T, typename Compare >
  RBTree< T, Compare > & RBTree< T, Compare >::operator=(std::initializer_list< value_type > init)
  {
    RBTree< T, Compare > temp(init);
    swap(temp);
    return *this;
  }

  template< typename T, typename Compare >
  typename RBTree< T, Compare >::iterator RBTree< T, Compare >::begin() noexcept
  {
    return data_.begin();
  }

  template< typename T, typename Compare >
  typename RBTree< T, Compare >::const_iterator RBTree< T, Compare >::begin() const noexcept
  {
    return data_.begin();
  }

  template< typename T, typename Compare >
  typename RBTree< T, Compare >::const_iterator RBTree< T, Compare >::cbegin() const noexcept
  {
    return data_.cbegin();
  }

  template< typename T, typename Compare >
  typename RBTree< T, Compare >::iterator RBTree< T, Compare >::end() noexcept
  {
    return data_.end();
  }

  template< typename T, typename Compare >
  typename RBTree< T, Compare >::const_iterator RBTree< T, Compare >::end() const noexcept
  {
    return data_.end();
  }

  template< typename T, typename Compare >
  typename RBTree< T, Compare >::const_iterator RBTree< T, Compare >::cend() const noexcept
  {
    return data_.cend();
  }

  template< typename T, typename Compare >
  bool RBTree< T, Compare >::empty() const noexcept
  {
    return data_.empty();
  }

  template< typename T, typename Compare >
  size_t RBTree< T, Compare >::size() const noexcept
  {
    return data_.size();
  }

  template< typename T, typename Compare >
  void RBTree< T, Compare >::clear() noexcept
  {
    data_.clear();
  }

  template< typename T, typename Compare >
  std::pair<
      typename RBTree< T, Compare >::iterator,
      bool
  > RBTree< T, Compare >::insert(const_reference value)
  {
    auto res = data_.insert(value);
    if (res.second)
    {
      res.first.node_->color_ = 'r';
      balanceTreeAfterInsert(res.first.node_);
      if (data_.data_.fake_->parent_->left_ != data_.data_.fake_)
      {
        data_.data_.fake_->parent_ = data_.data_.fake_->parent_->left_;
      }
      if (data_.data_.fake_->right_->right_ != data_.data_.fake_)
      {
        data_.data_.fake_->right_ = data_.data_.fake_->right_->right_;
      }
    }
    return res;
  }

  template< typename T, typename Compare >
  template< typename P >
  std::pair<
      typename RBTree< T, Compare >::iterator,
      bool
  > RBTree< T, Compare >::insert(P && value)
  {
    static_assert(std::is_constructible< value_type, P&& >::value, "Value type doesn't constructible from type you try to insert");
    const value_type val(value);
    return insert(val);
  }

  template< typename T, typename Compare >
  typename RBTree< T, Compare >::iterator RBTree< T, Compare >::insert(const_iterator pos, const_reference value)
  {
    bool was_inserted = false;
    auto moved_pos = pos;
    --moved_pos;
    if (*moved_pos == value)
    {
      was_inserted = true;
    }
    iterator res = data_.insert(pos, value);
    if (was_inserted)
    {
      res.node_->color_ = 'r';
      balanceTreeAfterInsert(res.node_);
    }
    return res;
  }

  template< typename T, typename Compare >
  template< typename P >
  typename RBTree< T, Compare >::iterator RBTree< T, Compare >::insert(const_iterator pos, P && value)
  {
    static_assert(std::is_constructible< value_type, P&& >::value, "Value type doesn't constructible from type you try to insert");
    const value_type val(value);
    return insert(pos, val);
  }

  template< typename T, typename Compare >
  template< typename InputIt >
  void RBTree< T, Compare >::insert(InputIt first, InputIt last)
  {
    while (first != last)
    {
      insert(*first++);
    }
  }

  template< typename T, typename Compare >
  void RBTree< T, Compare >::insert(std::initializer_list< value_type > init)
  {
    insert(init.begin(), init.end());
  }

  template< typename T, typename Compare >
  template< typename... Args >
  std::pair<
      typename RBTree< T, Compare >::iterator,
      bool
  > RBTree< T, Compare >::emplace(Args && ... args)
  {
    value_type val(std::forward< Args >(args)...);
    return insert(val);
  }

  template< typename T, typename Compare >
  template< typename... Args >
  typename RBTree< T, Compare >::iterator RBTree< T, Compare >::emplace_hint(const_iterator hint, Args && ... args)
  {
    value_type val(std::forward< Args >(args)...);
    return insert(hint, val);
  }

  template< typename T, typename Compare >
  typename RBTree< T, Compare >::reference RBTree< T, Compare >::at(const_reference value)
  {
    return data_.at(value);
  }

  template< typename T, typename Compare >
  typename RBTree< T, Compare >::const_reference RBTree< T, Compare >::at(const_reference value) const
  {
    return data_.at(value);
  }

  template< typename T, typename Compare >
  typename RBTree< T, Compare >::reference RBTree< T, Compare >::operator[](const_reference value)
  {
    try
    {
      return at(value);
    }
    catch (const std::out_of_range & e)
    {}
    return *(emplace(value).first);
  }

  template< typename T, typename Compare >
  typename RBTree< T, Compare >::reference RBTree< T, Compare >::operator[](value_type && value)
  {
    return (*this)[value];
  }

  template< typename T, typename Compare >
  typename RBTree< T, Compare >::iterator RBTree< T, Compare >::erase(iterator pos)
  {
    return erase(const_iterator(pos));
  }

  template< typename T, typename Compare >
  typename RBTree< T, Compare >::iterator RBTree< T, Compare >::erase(const_iterator pos)
  {
    Tree< T, Compare > * todel = pos.node_;
    ++pos;
    Tree< T, Compare > * swapped = todel;
    if (todel->left_ == data_.data_.fake_)
    {
      balanceTreeErase(todel);
      todel->parent_->left_ == todel ? todel->parent_->left_ = todel->right_ : todel->parent_->right_ = todel->right_;
      if (todel->right_ != data_.data_.fake_)
      {
        todel->right_->parent_ = todel->parent_;
      }
    }
    else
    {
      todel = todel->left_;
      while (todel->right_ != data_.data_.fake_)
      {
        todel = todel->right_;
      }
      std::swap(swapped->data_, todel->data_);
      balanceTreeErase(todel);
      todel->parent_->right_ == todel ? todel->parent_->right_ = todel->left_ : todel->parent_->left_ = todel->left_;
      if (todel->left_ != data_.data_.fake_)
      {
        todel->left_->parent_ = todel->parent_;
      }
    }
    if (data_.data_.fake_->parent_ == todel)
    {
      data_.data_.fake_->parent_ = (++iterator(todel, data_.data_.fake_)).node_;
    }
    if (data_.data_.fake_->right_ == todel)
    {
      data_.data_.fake_->right_ = (--iterator(todel, data_.data_.fake_)).node_;
    }
    delete todel;
    --data_.data_.size_;
    return iterator(pos.node_, data_.data_.fake_);
  }

  template< typename T, typename Compare >
  typename RBTree< T, Compare >::iterator RBTree< T, Compare >::erase(const_iterator first, const_iterator last)
  {
    while (first != last)
    {
      first = erase(first);
    }
    return first;
  }

  template< typename T, typename Compare >
  typename RBTree< T, Compare >::size_type RBTree< T, Compare >::erase(const_reference value)
  {
    const_iterator cit = find(value);
    if (cit != cend())
    {
      erase(cit);
      return 1ull;
    }
    return 0ull;
  }

  template< typename T, typename Compare >
  void RBTree< T, Compare >::swap(this_t & other)
  {
    data_.swap(other.data_);
  }

  template< typename T, typename Compare >
  typename RBTree< T, Compare >::size_type RBTree< T, Compare >::count(const_reference value) const
  {
    return data_.count(value);
  }

  template< typename T, typename Compare >
  typename RBTree< T, Compare >::iterator RBTree< T, Compare >::find(const_reference value)
  {
    return data_.find(value);
  }

  template< typename T, typename Compare >
  typename RBTree< T, Compare >::const_iterator RBTree< T, Compare >::find(const_reference value) const
  {
    return data_.find(value);
  }

  template< typename T, typename Compare >
  std::pair<
    typename RBTree< T, Compare >::iterator,
    typename RBTree< T, Compare >::iterator
  > RBTree< T, Compare >::equal_range(const_reference value)
  {
    return data_.equal_range(value);
  }

  template< typename T, typename Compare >
  std::pair<
    typename RBTree< T, Compare >::const_iterator,
    typename RBTree< T, Compare >::const_iterator
  > RBTree< T, Compare >::equal_range(const_reference value) const
  {
    return data_.equal_range(value);
  }

  template< typename T, typename Compare >
  typename RBTree< T, Compare >::iterator RBTree< T, Compare >::lower_bound(const_reference value)
  {
    return data_.lower_bound(value);
  }

  template< typename T, typename Compare >
  typename RBTree< T, Compare >::const_iterator RBTree< T, Compare >::lower_bound(const_reference value) const
  {
    return data_.lower_bound(value);
  }

  template< typename T, typename Compare >
  typename RBTree< T, Compare >::iterator RBTree< T, Compare >::upper_bound(const_reference value)
  {
    return data_.upper_bound(value);
  }

  template< typename T, typename Compare >
  typename RBTree< T, Compare >::const_iterator RBTree< T, Compare >::upper_bound(const_reference value) const
  {
    return data_.upper_bound(value);
  }

  template< typename T, typename Compare >
  typename RBTree< T, Compare >::value_compare RBTree< T, Compare >::value_comp() const
  {
    return data_.value_comp();
  }

  template< typename T, typename Compare >
  void RBTree< T, Compare >::balanceTreeAfterInsert(Tree< T, Compare > * inserted)
  {
    Tree< T, Compare > * par = inserted->parent_;
    if (par->color_ == 'b')
    {
      return;
    }
    if (data_.data_.fake_->left_ == par)
    {
      par->color_ = 'b';
      return;
    }
    Tree< T, Compare > * grandpa = par->parent_;
    Tree< T, Compare > * uncle = (grandpa->left_ == par) ? grandpa->right_ : grandpa->left_;
    if (uncle->color_ == 'r')
    {
      par->color_ = uncle->color_ = 'b';
      grandpa->color_ = 'r';
      balanceTreeAfterInsert(grandpa);
    }
    else
    {
      if (grandpa->left_ == par && par->left_ == inserted)
      {
        par->color_ = 'b';
        grandpa->color_ = 'r';
        data_.rotateRightRight(par);
      }
      else if (grandpa->right_ == par && par->right_ == inserted)
      {
        par->color_ = 'b';
        grandpa->color_ = 'r';
        data_.rotateLeftLeft(par);
      }
      else if (par->right_ == inserted)
      {
        data_.rotateLeftLeft(inserted);
        balanceTreeAfterInsert(inserted->left_);
      }
      else
      {
        data_.rotateRightRight(inserted);
        balanceTreeAfterInsert(inserted->right_);
      }
    }
  }

  template< typename T, typename Compare >
  void RBTree< T, Compare >::balanceTreeErase(Tree< T, Compare > * todel)
  {
    if (todel->color_ == 'r')
    {
      return;
    }
    else
    {
      if (todel->left_->color_ == 'r')
      {
        todel->left_->color_ = 'b';
        return;
      }
      auto par = todel->parent_;
      auto sibling = (par->left_ == todel ? par->right_ : par->left_);
      auto out_nep = (par->left_ == sibling ? sibling->left_ : sibling->right_);
      auto in_nep = (par->left_ == sibling ? sibling->right_ : sibling->left_);
      if (out_nep->color_ == 'r')
      {
        if (par->right_ == sibling)
        {
          data_.rotateLeftLeft(sibling);
        }
        else
        {
          data_.rotateRightRight(sibling);
        }
        out_nep->color_ = 'b';
      }
      else if (in_nep->color_ == 'r')
      {
        if (sibling->left_ == in_nep)
        {
          data_.rotateRightRight(in_nep);
        }
        else
        {
          data_.rotateLeftLeft(in_nep);
        }
        in_nep->color_ = 'b';
        sibling->color_ = 'r';
      }
      else
      {
        if (par->color_ == 'r')
        {
          par->color_ = 'b';
          sibling->color_ = 'r';
        }
        else if (sibling->color_ == 'r')
        {
          data_.rotateLeftLeft(sibling);
          sibling->color_ = 'b';
          par->color_ = 'r';
          balanceTreeErase(todel);
        }
        else
        {
          sibling->color_ = 'r';
          balanceTreeAfterInsert(par);
        }
      }
    }
  }
}

#endif
