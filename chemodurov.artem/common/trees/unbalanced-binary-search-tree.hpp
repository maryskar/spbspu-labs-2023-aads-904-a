#ifndef S4_UNBALANCED_BINARY_SEARCH_TREE_HPP
#define S4_UNBALANCED_BINARY_SEARCH_TREE_HPP
#include <functional>
#include <stdexcept>
#include "bidirectional-iterator.hpp"
#include "const-bidirectional-iterator.hpp"

namespace chemodurov
{
  template< typename T, typename Compare >
  class RotatableBinarySearchTree;

  template< typename T, typename Compare >
  class RBTree;

  template< typename T, typename Compare = std::less<> >
  class UnbalancedBinarySearchTree
  {
    friend class BidirectionalIterator< T, Compare >;
    friend class RotatableBinarySearchTree< T, Compare >;
    friend class RBTree< T, Compare >;
   public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using value_compare = Compare;
    using reference = value_type &;
    using const_reference = const value_type &;
    using iterator = BidirectionalIterator< value_type, value_compare >;
    using const_iterator = ConstBidirectionalIterator< value_type, value_compare >;
    using this_t = UnbalancedBinarySearchTree< value_type, value_compare >;
    UnbalancedBinarySearchTree();
    UnbalancedBinarySearchTree(const this_t & other);
    UnbalancedBinarySearchTree(this_t && other) noexcept;
    explicit UnbalancedBinarySearchTree(const value_compare & comp);
    template< typename InputIt >
    UnbalancedBinarySearchTree(InputIt first, InputIt last, const value_compare & comp = value_compare());
    UnbalancedBinarySearchTree(std::initializer_list< value_type > init, const value_compare & comp = value_compare());
    ~UnbalancedBinarySearchTree();
    this_t & operator=(const this_t & other);
    this_t & operator=(this_t && other) noexcept;
    this_t & operator=(std::initializer_list< value_type > init);
    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;
    iterator last() noexcept;
    const_iterator last() const noexcept;
    const_iterator clast() const noexcept;
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
    Tree< T, Compare > * fake_;
    Compare comp_;
    std::size_t size_;
    void swapPointers(Tree< T, Compare > * lhs, Tree< T, Compare > * rhs);
    Tree< T, Compare > * swapBeforeErase(const_iterator cit);
    iterator deleteMaxLeft(Tree< T, Compare > * todel);
  };

  template< typename T, typename Compare >
  UnbalancedBinarySearchTree< T, Compare >::UnbalancedBinarySearchTree():
   fake_(static_cast< Tree< T, Compare > * >(::operator new(sizeof(Tree< T, Compare >)))),
   comp_(),
   size_(0)
  {
    fake_->left_ = fake_;
    fake_->right_ = fake_;
    fake_->parent_ = fake_;
  }

  template< typename T, typename Compare >
  typename UnbalancedBinarySearchTree< T, Compare >::iterator UnbalancedBinarySearchTree< T, Compare >::begin() noexcept
  {
    return iterator(fake_->parent_, fake_);
  }

  template< typename T, typename Compare >
  typename UnbalancedBinarySearchTree< T, Compare >::const_iterator
  UnbalancedBinarySearchTree< T, Compare >::begin() const noexcept
  {
    return cbegin();
  }

  template< typename T, typename Compare >
  typename UnbalancedBinarySearchTree< T, Compare >::const_iterator
  UnbalancedBinarySearchTree< T, Compare >::cbegin() const noexcept
  {
    return const_iterator(fake_->parent_, fake_);
  }

  template< typename T, typename Compare >
  typename UnbalancedBinarySearchTree< T, Compare >::iterator UnbalancedBinarySearchTree< T, Compare >::last() noexcept
  {
    return iterator(fake_->right_, fake_);
  }

  template< typename T, typename Compare >
  typename UnbalancedBinarySearchTree< T, Compare >::const_iterator
  UnbalancedBinarySearchTree< T, Compare >::last() const noexcept
  {
    return cbegin();
  }

  template< typename T, typename Compare >
  typename UnbalancedBinarySearchTree< T, Compare >::const_iterator
  UnbalancedBinarySearchTree< T, Compare >::clast() const noexcept
  {
    return const_iterator(fake_->right_, fake_);
  }

  template< typename T, typename Compare >
  typename UnbalancedBinarySearchTree< T, Compare >::iterator UnbalancedBinarySearchTree< T, Compare >::end() noexcept
  {
    return iterator(fake_, fake_);
  }

  template< typename T, typename Compare >
  typename UnbalancedBinarySearchTree< T, Compare >::const_iterator
  UnbalancedBinarySearchTree< T, Compare >::end() const noexcept
  {
    return cend();
  }

  template< typename T, typename Compare >
  typename UnbalancedBinarySearchTree< T, Compare >::const_iterator
  UnbalancedBinarySearchTree< T, Compare >::cend() const noexcept
  {
    return const_iterator(fake_, fake_);
  }

  template< typename T, typename Compare >
  bool UnbalancedBinarySearchTree< T, Compare >::empty() const noexcept
  {
    return !size_;
  }

  template< typename T, typename Compare >
  size_t UnbalancedBinarySearchTree< T, Compare >::size() const noexcept
  {
    return size_;
  }

  template< typename T, typename Compare >
  void clearTree(Tree< T, Compare > * root, Tree< T, Compare > * fake)
  {
    if (root == fake)
    {
      return;
    }
    clearTree(root->left_, fake);
    clearTree(root->right_, fake);
    delete root;
  }

  template< typename T, typename Compare >
  void UnbalancedBinarySearchTree< T, Compare >::clear() noexcept
  {
    clearTree(fake_->left_, fake_);
    fake_->left_ = fake_;
    fake_->right_ = fake_;
    fake_->parent_ = fake_;
  }

  template< typename T, typename Compare >
  UnbalancedBinarySearchTree< T, Compare >::~UnbalancedBinarySearchTree()
  {
    clear();
    ::operator delete(fake_);
  }

  template< typename T, typename Compare >
  typename UnbalancedBinarySearchTree< T, Compare >::const_iterator
      UnbalancedBinarySearchTree< T, Compare >::lower_bound(const_reference value) const
  {
    Tree< T, Compare > * temp = fake_->left_;
    value_compare comp = value_comp();
    while (temp != fake_)
    {
      if (comp(value, temp->data_))
      {
        if (temp->left_ != fake_)
        {
          temp = temp->left_;
        }
        else
        {
          return const_iterator(temp, fake_);
        }
      }
      else if (!comp(value, temp->data_) && !comp(temp->data_, value))
      {
        return const_iterator(temp, fake_);
      }
      else
      {
        if (temp->right_ != fake_)
        {
          temp = temp->right_;
        }
        else
        {
          return ++const_iterator(temp, fake_);
        }
      }
    }
    return cend();
  }

  template< typename T, typename Compare >
  typename UnbalancedBinarySearchTree< T, Compare >::iterator
        UnbalancedBinarySearchTree< T, Compare >::lower_bound(const_reference value)
  {
    const_iterator cit = (static_cast< const this_t & >(*this)).lower_bound(value);
    return iterator(cit.node_, cit.fake_);
  }

  template< typename T, typename Compare >
  typename UnbalancedBinarySearchTree< T, Compare >::const_iterator
      UnbalancedBinarySearchTree< T, Compare >::upper_bound(const_reference value) const
  {
    const_iterator cit = lower_bound(value);
    const_iterator moved_cit = cit;
    return (cit == cend()) ? cend() : ((!value_comp()(*cit, value) && !value_comp()(value, *cit)) ? ++moved_cit : cit);
  }

  template< typename T, typename Compare >
  typename UnbalancedBinarySearchTree< T, Compare >::iterator
      UnbalancedBinarySearchTree< T, Compare >::upper_bound(const_reference value)
  {
    const_iterator cit = (static_cast< const this_t & >(*this)).upper_bound(value);
    return iterator(cit.node_, cit.fake_);
  }

  template< typename T, typename Compare >
  typename UnbalancedBinarySearchTree< T, Compare >::value_compare
      UnbalancedBinarySearchTree< T, Compare >::value_comp() const
  {
    return comp_;
  }

  template< typename T, typename Compare >
  void UnbalancedBinarySearchTree< T, Compare >::swap(this_t & other)
  {
    std::swap(comp_, other.comp_);
    std::swap(fake_, other.fake_);
    std::swap(size_, other.size_);
  }

  template< typename T, typename Compare >
  std::pair<
      typename UnbalancedBinarySearchTree< T, Compare >::const_iterator,
      typename UnbalancedBinarySearchTree< T, Compare >::const_iterator
  > UnbalancedBinarySearchTree< T, Compare >::equal_range(const_reference value) const
  {
    return {lower_bound(value), upper_bound(value)};
  }

  template< typename T, typename Compare >
  std::pair<
      typename UnbalancedBinarySearchTree< T, Compare >::iterator,
      typename UnbalancedBinarySearchTree< T, Compare >::iterator
  > UnbalancedBinarySearchTree< T, Compare >::equal_range(const_reference value)
  {
    return {lower_bound(value), upper_bound(value)};
  }

  template< typename T, typename Compare >
  typename UnbalancedBinarySearchTree< T, Compare >::const_iterator
      UnbalancedBinarySearchTree< T, Compare >::find(const_reference value) const
  {
    const_iterator cit = lower_bound(value);
    return cit == cend() ? cit : ((!value_comp()(*cit, value) && !value_comp()(value, *cit)) ? cit : cend());
  }

  template< typename T, typename Compare >
  typename UnbalancedBinarySearchTree< T, Compare >::iterator
      UnbalancedBinarySearchTree< T, Compare >::find(const_reference value)
  {
    const_iterator cit = static_cast< const this_t & >(*this).find(value);
    return iterator(cit.node_, cit.fake_);
  }

  template< typename T, typename Compare >
  typename UnbalancedBinarySearchTree< T, Compare >::size_type
      UnbalancedBinarySearchTree< T, Compare >::count(const_reference value) const
  {
    return (find(value) == end()) ? 0ull : 1ull;
  }

  template< typename T, typename Compare >
  std::pair<
      typename UnbalancedBinarySearchTree< T, Compare >::iterator,
      bool
  > UnbalancedBinarySearchTree< T, Compare >::insert(const_reference value)
  {
    iterator it = lower_bound(value);
    if (it == end())
    {
      if (empty())
      {
        fake_->left_ = new Tree< T, Compare >{value, fake_, fake_, fake_, '0'};
        fake_->right_ = fake_->left_;
        fake_->parent_ = fake_->left_;
      }
      else
      {
        fake_->right_->right_ = new Tree< T, Compare >{value, fake_, fake_, fake_->right_, '0'};
        fake_->right_ = fake_->right_->right_;
      }
      ++size_;
      return {iterator(fake_->right_, fake_), true};
    }
    if (!value_comp()(*it, value) && !value_comp()(value, *it))
    {
      return {it, false};
    }
    if (it.node_->left_ == fake_)
    {
      it.node_->left_ = new Tree< T, Compare >{value, fake_, fake_, it.node_, '0'};
      it.node_ = it.node_->left_;
    }
    else
    {
      it.node_ = it.node_->left_;
      while (it.node_->right_ != fake_)
      {
        it.node_ = it.node_->right_;
      }
      it.node_->right_ = new Tree< T, Compare >{value, fake_, fake_, it.node_, '0'};
      it.node_ = it.node_->right_;
    }
    if (it.node_->parent_ == begin().node_ && it.node_->parent_->left_ == it.node_)
    {
      fake_->parent_ = it.node_;
    }
    ++size_;
    return {iterator(it.node_, fake_), true};
  }

  template< typename T, typename Compare >
  template< typename P >
  std::pair<
      typename UnbalancedBinarySearchTree< T, Compare >::iterator,
      bool
  > UnbalancedBinarySearchTree< T, Compare >::insert(P && value)
  {
    static_assert(std::is_constructible< value_type, P&& >::value, "Value type doesn't constructible from type you try to insert");
    const value_type val(std::forward< P >(value));
    return insert(val);
  }

  template< typename T, typename Compare >
  typename UnbalancedBinarySearchTree< T, Compare >::iterator
      UnbalancedBinarySearchTree< T, Compare >::insert(const_iterator pos, const_reference value)
  {
    if (value_comp()(value, *pos) && value_comp()(*(--pos), value))
    {
      pos.node_->left_ = new Tree< T, Compare >{value, pos.node_->left_, fake_, pos.node_, '0'};
      ++size_;
      return iterator(pos.node_->left_, fake_);
    }
    return insert(value);
  }

  template< typename T, typename Compare >
  template< typename P >
  typename UnbalancedBinarySearchTree< T, Compare >::iterator
      UnbalancedBinarySearchTree< T, Compare >::insert(const_iterator pos, P && value)
  {
    static_assert(std::is_constructible< value_type, P&& >::value, "Value type isn't constructible from type you try to insert");
    const value_type val(std::forward< P >(value));
    return insert(pos, val);
  }

  template< typename T, typename Compare >
  template< typename InputIt >
  void UnbalancedBinarySearchTree< T, Compare >::insert(InputIt first, InputIt last)
  {
    while (first != last)
    {
      insert(*first++);
    }
  }

  template< typename T, typename Compare >
  void UnbalancedBinarySearchTree< T, Compare >::insert(std::initializer_list< value_type > init)
  {
    insert(init.begin(), init.end());
  }

  template< typename T, typename Compare >
  template< typename... Args >
  std::pair<
      typename UnbalancedBinarySearchTree< T, Compare >::iterator,
      bool
  > UnbalancedBinarySearchTree< T, Compare >::emplace(Args && ... args)
  {
    value_type val(std::forward< Args >(args)...);
    return insert(std::move(val));
  }

  template< typename T, typename Compare >
  template< typename... Args >
  typename UnbalancedBinarySearchTree< T, Compare >::iterator
      UnbalancedBinarySearchTree< T, Compare >::emplace_hint(const_iterator hint, Args && ... args)
  {
    value_type val(std::forward< Args >(args)...);
    return insert(hint, std::move(val));
  }

  template< typename T, typename Compare >
  const T & UnbalancedBinarySearchTree< T, Compare >::at(const_reference value) const
  {
    const_iterator cit = find(value);
    if (cit == cend())
    {
      throw std::out_of_range("No such value in tree");
    }
    return *cit;
  }

  template< typename T, typename Compare >
  T & UnbalancedBinarySearchTree< T, Compare >::at(const_reference value)
  {
    return const_cast< T & >((static_cast< const this_t & >(*this)).at(value));
  }

  template< typename T, typename Compare >
  T & UnbalancedBinarySearchTree< T, Compare >::operator[](const_reference value)
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
  T & UnbalancedBinarySearchTree< T, Compare >::operator[](value_type && value)
  {
    return (*this)[value];
  }

  template< typename T, typename Compare >
  typename UnbalancedBinarySearchTree< T, Compare >::iterator
      UnbalancedBinarySearchTree< T, Compare >::erase(iterator pos)
  {
    return erase(const_iterator(pos));
  }

  template< typename T, typename Compare >
  typename UnbalancedBinarySearchTree< T, Compare >::iterator
      UnbalancedBinarySearchTree< T, Compare >::erase(const_iterator pos)
  {
    Tree< T, Compare > * todel = swapBeforeErase(pos);
    return deleteMaxLeft(todel);
  }

  template< typename T, typename Compare >
  typename UnbalancedBinarySearchTree< T, Compare >::iterator
      UnbalancedBinarySearchTree< T, Compare >::erase(const_iterator first, const_iterator last)
  {
    while (first != last)
    {
      first = erase(first);
    }
    return iterator(first.node_, fake_);
  }

  template< typename T, typename Compare >
  typename UnbalancedBinarySearchTree< T, Compare >::size_type
      UnbalancedBinarySearchTree< T, Compare >::erase(const_reference value)
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
  UnbalancedBinarySearchTree< T, Compare >::UnbalancedBinarySearchTree(const value_compare & comp):
   UnbalancedBinarySearchTree()
  {
    comp_ = comp;
  }

  template< typename T, typename Compare >
  template< typename InputIt >
  UnbalancedBinarySearchTree< T, Compare >::UnbalancedBinarySearchTree(InputIt first, InputIt last, const value_compare & comp):
   UnbalancedBinarySearchTree(comp)
  {
    insert< InputIt >(first, last);
  }

  template< typename T, typename Compare >
  UnbalancedBinarySearchTree< T, Compare >::UnbalancedBinarySearchTree(const this_t & other):
    UnbalancedBinarySearchTree(other.begin(), other.end(), Compare())
  {}

  template< typename T, typename Compare >
  UnbalancedBinarySearchTree< T, Compare >::UnbalancedBinarySearchTree(this_t && other) noexcept:
   UnbalancedBinarySearchTree()
  {
    swap(other);
  }

  template< typename T, typename Compare >
  UnbalancedBinarySearchTree< T, Compare >::UnbalancedBinarySearchTree(std::initializer_list< value_type > init,
      const value_compare & comp):
   UnbalancedBinarySearchTree(init.begin(), init.end(), comp)
  {}

  template< typename T, typename Compare >
  UnbalancedBinarySearchTree< T, Compare > & UnbalancedBinarySearchTree< T, Compare >::operator=(const this_t & other)
  {
    if (this == std::addressof(other))
    {
      return *this;
    }
    this_t temp(other);
    clear();
    swap(temp);
    return *this;
  }

  template< typename T, typename Compare >
  UnbalancedBinarySearchTree< T, Compare > & UnbalancedBinarySearchTree< T, Compare >::operator=(this_t && other) noexcept
  {
    if (this == std::addressof(other))
    {
      return *this;
    }
    clear();
    swap(other);
    return *this;
  }

  template< typename T, typename Compare >
  UnbalancedBinarySearchTree< T, Compare > &
      UnbalancedBinarySearchTree< T, Compare >::operator=(std::initializer_list< value_type > init)
  {
    this_t temp(init);
    clear();
    swap(temp);
    return *this;
  }

  template< typename T, typename Compare >
  typename UnbalancedBinarySearchTree< T, Compare >::iterator
      UnbalancedBinarySearchTree< T, Compare >::deleteMaxLeft(Tree< T, Compare > * todel)
  {
    iterator pos(todel, fake_);
    ++pos;
    if (todel->left_ == fake_)
    {
      todel->parent_->left_ == todel ? todel->parent_->left_ = todel->right_ : todel->parent_->right_ = todel->right_;
      if (todel->right_ != fake_)
      {
        todel->right_->parent_ = todel->parent_;
      }
    }
    else
    {
      todel->parent_->right_ == todel ? todel->parent_->right_ = todel->left_ : todel->parent_->left_ = todel->left_;
      if (todel->left_ != fake_)
      {
        todel->left_->parent_ = todel->parent_;
      }
    }
    if (fake_->parent_ == todel)
    {
      fake_->parent_ = (++iterator(todel, fake_)).node_;
    }
    if (fake_->right_ == todel)
    {
      fake_->right_ = (--iterator(todel, fake_)).node_;
    }
    delete todel;
    --size_;
    return pos;
  }

  template< typename T, typename Compare >
  void UnbalancedBinarySearchTree< T, Compare >::swapPointers(Tree< T, Compare > * lhs, Tree< T, Compare > * rhs)
  {
    if (lhs == fake_ || rhs == fake_ || lhs == rhs)
    {
      return;
    }
    Tree< T, Compare > * temp = nullptr;
    if (lhs->parent_ != rhs)
    {
      if (lhs->parent_ != fake_)
      {
        lhs->parent_->left_ == lhs ? lhs->parent_->left_ = rhs : lhs->parent_->right_ = rhs;
      }
      else
      {
        lhs->parent_->left_ = rhs;
      }
    }
    if (rhs->parent_ != lhs)
    {
      if (rhs->parent_ != fake_)
      {
        rhs->parent_->left_ == rhs ? rhs->parent_->left_ = lhs : rhs->parent_->right_ = lhs;
      }
      else
      {
        rhs->parent_->left_ = lhs;
      }
    }
    if (lhs->left_ != fake_ && lhs->left_ != rhs)
    {
      lhs->left_->parent_ = rhs;
    }
    if (lhs->right_ != fake_ && lhs->right_ != rhs)
    {
      lhs->right_->parent_ = rhs;
    }
    if (rhs->left_ != fake_ && rhs->left_ != lhs)
    {
      rhs->left_->parent_ = lhs;
    }
    if (rhs->right_ != fake_ && rhs->right_ != lhs)
    {
      rhs->right_->parent_ = lhs;
    }
    if (rhs->parent_ != lhs && lhs->parent_ != rhs)
    {
      std::swap(lhs->parent_, rhs->parent_);
    }
    else if (lhs->parent_ == rhs)
    {
      temp = rhs->parent_;
      rhs->parent_ = lhs;
      lhs->parent_ = temp;
    }
    else
    {
      temp = lhs->parent_;
      lhs->parent_ = rhs;
      rhs->parent_ = temp;
    }
    if (lhs->right_ != rhs && rhs->right_ != lhs)
    {
      std::swap(lhs->right_, rhs->right_);
    }
    else if (lhs->right_ == rhs)
    {
      temp = rhs->right_;
      rhs->right_ = lhs;
      lhs->right_ = temp;
    }
    else
    {
      temp = lhs->right_;
      lhs->right_ = rhs;
      rhs->right_ = temp;
    }
    if (lhs->left_ != rhs && rhs->left_ != lhs)
    {
      std::swap(lhs->left_, rhs->left_);
    }
    else if (lhs->left_ == rhs)
    {
      temp = rhs->left_;
      rhs->left_ = lhs;
      lhs->left_ = temp;
    }
    else
    {
      temp = lhs->left_;
      lhs->left_ = rhs;
      rhs->left_ = temp;
    }
  }

  template< typename T, typename Compare >
  Tree< T, Compare > * UnbalancedBinarySearchTree< T, Compare >::swapBeforeErase(const_iterator cit)
  {
    Tree< T, Compare > * todel = cit.node_;
    Tree< T, Compare > * swapped = todel;
    if (todel->left_ != fake_)
    {
      todel = todel->left_;
      while (todel->right_ != fake_)
      {
        todel = todel->right_;
      }
      swapPointers(todel, swapped);
    }
    return swapped;
  }

  template< typename T, typename Compare >
  bool operator==(const UnbalancedBinarySearchTree< T, Compare > & lhs, const UnbalancedBinarySearchTree< T, Compare > & rhs)
  {
    if (lhs.size() != rhs.size())
    {
      return false;
    }
    for (auto i = lhs.cbegin(), j = rhs.cbegin(); i != lhs.cend(); ++i, ++j)
    {
      if (*i != *j)
      {
        return false;
      }
    }
    return true;
  }

  template< typename T, typename Compare >
  bool operator!=(const UnbalancedBinarySearchTree< T, Compare > & lhs, const UnbalancedBinarySearchTree< T, Compare > & rhs)
  {
    return !(lhs == rhs);
  }
}

#endif
