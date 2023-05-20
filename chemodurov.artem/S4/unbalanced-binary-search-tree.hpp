#ifndef S4_UNBALANCED_BINARY_SEARCH_TREE_HPP
#define S4_UNBALANCED_BINARY_SEARCH_TREE_HPP
#include <functional>
#include "bidirectional-iterator.hpp"
#include "const-bidirectional-iterator.hpp"

namespace chemodurov
{
  template< typename T, typename Compare = std::less<> >
  class UnbalancedBinarySearchTree
  {
    friend class BidirectionalIterator< T, Compare >;
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
    UnbalancedBinarySearchTree(this_t && other);
    explicit UnbalancedBinarySearchTree(const value_compare & comp);
    template< typename InputIt >
    UnbalancedBinarySearchTree(InputIt first, InputIt last, const value_compare & comp = value_compare());
    UnbalancedBinarySearchTree(std::initializer_list< value_type > init, const value_compare & comp = value_compare());
    ~UnbalancedBinarySearchTree();
    this_t & operator=(const this_t & other);
    this_t & operator=(this_t && other);
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
    Tree< T, Compare > * fake_;
    Compare comp_;
    std::size_t size_;
  };

  template< typename T, typename Compare >
  UnbalancedBinarySearchTree< T, Compare >::UnbalancedBinarySearchTree():
   fake_(::operator new(sizeof(Tree< T, Compare >))),
   comp_(),
   size_(0)
  {
    fake_->left_ = nullptr;
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
    const_iterator cit = const_iterator(fake_->left_);
    const_iterator moved_cit = cit;
    value_compare comp = value_comp();
    while (!comp(*cit, value) || comp(value, *(++moved_cit)))
    {
      if (!comp(*cit, value) && cit.node_->left != cit.node_->fake_)
      {
        cit.node_ = cit.node_->left_;
      }
      else if (comp(value, *moved_cit) && cit.node_->left != cit.node_->fake_)
      {
        cit.node_ = cit.node_->right_;
      }
      else
      {
        return moved_cit;
      }
      moved_cit = cit;
    }
    return moved_cit;
  }

  template< typename T, typename Compare >
  typename UnbalancedBinarySearchTree< T, Compare >::iterator
        UnbalancedBinarySearchTree< T, Compare >::lower_bound(const_reference value)
  {
    const_iterator cit = (static_cast< const this_t >(*this)).lower_bound(value);
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
    const_iterator cit = (static_cast< const this_t >(*this)).upper_bound(value);
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
    std::swap(fake_, other.fake_);
    std::swap(comp_, other.comp_);
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
    return (*cit == value) ? cit : cend();
  }

  template< typename T, typename Compare >
  typename UnbalancedBinarySearchTree< T, Compare >::iterator
      UnbalancedBinarySearchTree< T, Compare >::find(const_reference value)
  {
    const_iterator cit = find(value);
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
      (--end()).node_->right_ = new Tree< T, Compare >(value, fake_, fake_, (--end()).node_);
      return {--end(), true};
    }
    if (!value_comp()(*it, value) && !value_comp()(value, *it))
    {
      return {it, false};
    }
    Tree< T, Compare> * inserted = new Tree< T, Compare >(value, it.node_->left_, fake_, it.node_);
    it.node_->left_ = inserted;
    return {iterator(inserted, fake_), true};
  }

  template< typename T, typename Compare >
  template< typename P >
  std::pair<
      typename UnbalancedBinarySearchTree< T, Compare >::iterator,
      bool
  > UnbalancedBinarySearchTree< T, Compare >::insert(P && value)
  {
    static_assert(std::is_constructible< value_type, P&& >::value, "Value type isn't constructible from type you try to insert");
    value_type val(std::forward< P >(value));
    return insert(val);
  }

  template< typename T, typename Compare >
  typename UnbalancedBinarySearchTree< T, Compare >::iterator
      UnbalancedBinarySearchTree< T, Compare >::insert(const_iterator pos, const_reference value)
  {
    if (value_comp()(value, *pos) && value_comp()(*(--pos), value))
    {
      pos.node_->left_ = new Tree< T, Compare >(value, pos.node_->left_, fake_, pos.node_);
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
    value_type val(std::forward< P >(value));
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
    return const_cast< T & >((static_cast< const this_t >(*this)).at(value));
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
    Tree< T, Compare > * todel = pos.node_;
    ++pos;
    Tree< T, Compare > * swapped = todel;
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
      todel = todel->left_;
      while (todel->right_ != fake_)
      {
        todel = todel->right_;
      }
      std::swap(swapped->data_, todel->data_);
      todel->parent_->right_ == todel ? todel->parent_->right_ = fake_ : todel->parent_->left_ = fake_;
    }
    delete todel;
    return pos;
  }

  template< typename T, typename Compare >
  typename UnbalancedBinarySearchTree< T, Compare >::iterator
      UnbalancedBinarySearchTree< T, Compare >::erase(const_iterator first, const_iterator last)
  {
    while (first != last)
    {
      first = erase(first);
    }
    return first;
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
    insert(first, last);
  }

  template< typename T, typename Compare >
  UnbalancedBinarySearchTree< T, Compare >::UnbalancedBinarySearchTree(const this_t & other):
    UnbalancedBinarySearchTree(other.begin(), other.end(), Compare())
  {}

  template< typename T, typename Compare >
  UnbalancedBinarySearchTree< T, Compare >::UnbalancedBinarySearchTree(this_t && other):
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
  UnbalancedBinarySearchTree< T, Compare > & UnbalancedBinarySearchTree< T, Compare >::operator=(this_t && other)
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
}

#endif
