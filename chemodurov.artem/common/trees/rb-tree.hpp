#ifndef S4_RB_TREE_HPP
#define S4_RB_TREE_HPP
#include "rotatable-binary-search-tree.hpp"

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
    RBTree(const this_t & other);
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
    bool isEqual(const this_t & rhs) const;
   private:
    RotatableBinarySearchTree< T, Compare > data_;
    void balanceTreeAfterInsert(Tree< T, Compare > * inserted);
    void balanceTreeErase(Tree< T, Compare > * todel);
    bool isRed(const Tree< T, Compare > * node);
    bool isBlack(const Tree< T, Compare > * node);
    void setColor(Tree< T, Compare > * node, char color);
  };

  template< typename T, typename Compare >
  RBTree< T, Compare >::RBTree():
   data_()
  {
    setColor(data_.data_.fake_, 'b');
  }

  template< typename T, typename Compare >
  RBTree< T, Compare >::RBTree(const this_t & other):
   data_(other.begin(), other.end(), other.value_comp())
  {
    setColor(data_.data_.fake_, 'b');
  }

  template< typename T, typename Compare >
  RBTree< T, Compare >::RBTree(this_t && other) noexcept:
   data_(std::move(other.data_))
  {
    setColor(data_.data_.fake_, 'b');
  }

  template< typename T, typename Compare >
  RBTree< T, Compare >::RBTree(const value_compare & comp):
   data_(comp)
  {
    setColor(data_.data_.fake_, 'b');
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
  RBTree< T, Compare > & RBTree< T, Compare >::operator=(this_t && other) noexcept
  {
    if (this == std::addressof(other))
    {
      return *this;
    }
    clear();
    this_t temp(std::move(other));
    swap(temp);
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
  typename RBTree< T, Compare >::iterator RBTree< T, Compare >::last() noexcept
  {
    return data_.last();
  }

  template< typename T, typename Compare >
  typename RBTree< T, Compare >::const_iterator RBTree< T, Compare >::last() const noexcept
  {
    return data_.last();
  }

  template< typename T, typename Compare >
  typename RBTree< T, Compare >::const_iterator RBTree< T, Compare >::clast() const noexcept
  {
    return data_.clast();
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
      setColor(res.first.node_, 'r');
      balanceTreeAfterInsert(res.first.node_);
      if (left(parent(data_.data_.fake_)) != data_.data_.fake_)
      {
        setParent(data_.data_.fake_, left(parent(data_.data_.fake_)));
      }
      if (right(right(data_.data_.fake_)) != data_.data_.fake_)
      {
        setRight(data_.data_.fake_, right(right(data_.data_.fake_)));
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
      setColor(res.node_, 'r');
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
    Tree< T, Compare > * todel = data_.data_.swapBeforeErase(pos);
    balanceTreeErase(todel);
    return data_.data_.deleteMaxLeft(todel);
  }

  template< typename T, typename Compare >
  typename RBTree< T, Compare >::iterator RBTree< T, Compare >::erase(const_iterator first, const_iterator last)
  {
    while (first != last)
    {
      erase(first++);
    }
    return iterator(first.node_, data_.data_.fake_);
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
    Tree< T, Compare > * par = parent(inserted);
    if (isBlack(par))
    {
      return;
    }
    if (left(data_.data_.fake_) == par)
    {
      setColor(par, 'b');
      return;
    }
    Tree< T, Compare > * grandpa = parent(par);
    Tree< T, Compare > * uncle = (left(grandpa) == par) ? right(grandpa) : left(grandpa);
    if (isRed(uncle))
    {
      setColor(par, 'b');
      setColor(uncle, 'b');
      setColor(grandpa, 'r');
      balanceTreeAfterInsert(grandpa);
    }
    else
    {
      if (left(grandpa) == par && left(par) == inserted)
      {
        setColor(par, 'b');
        setColor(grandpa, 'r');
        data_.rotateRightRight(par);
      }
      else if (right(grandpa) == par && right(par) == inserted)
      {
        setColor(par, 'b');
        setColor(grandpa, 'r');
        data_.rotateLeftLeft(par);
      }
      else if (right(par) == inserted)
      {
        data_.rotateLeftLeft(inserted);
        balanceTreeAfterInsert(left(inserted));
      }
      else
      {
        data_.rotateRightRight(inserted);
        balanceTreeAfterInsert(right(inserted));
      }
    }
  }

  template< typename T, typename Compare >
  void RBTree< T, Compare >::balanceTreeErase(Tree< T, Compare > * todel)
  {
    if (isRed(todel))
    {
      return;
    }
    else
    {
      if (isRed(left(todel)))
      {
        setColor(left(todel), 'b');
        return;
      }
      auto par = parent(todel);
      auto sibling = (left(par) == todel ? right(par) : left(par));
      auto out_nep = (left(par) == sibling ? left(sibling) : right(sibling));
      auto in_nep = (left(par) == sibling ? right(sibling) : left(sibling));
      if (sibling == data_.data_.fake_)
      {
        out_nep = in_nep = sibling;
      }
      if (isRed(out_nep))
      {
        if (right(par) == sibling)
        {
          data_.rotateLeftLeft(sibling);
        }
        else
        {
          data_.rotateRightRight(sibling);
        }
        setColor(out_nep, 'b');
      }
      else if (isRed(in_nep))
      {
        if (left(sibling) == in_nep)
        {
          data_.rotateRightRight(in_nep);
        }
        else
        {
          data_.rotateLeftLeft(in_nep);
        }
        setColor(in_nep, 'b');
        setColor(sibling, 'r');
      }
      else
      {
        if (isRed(par))
        {
          setColor(par, 'b');
          setColor(sibling, 'r');
        }
        else if (isRed(sibling))
        {
          data_.rotateLeftLeft(sibling);
          setColor(sibling, 'b');
          setColor(par, 'r');
          balanceTreeErase(todel);
        }
        else
        {
          setColor(sibling, 'r');
          balanceTreeErase(par);
        }
      }
    }
  }

  template< typename T, typename Compare >
  bool RBTree< T, Compare >::isEqual(const this_t & rhs) const
  {
    return data_ == rhs.data_;
  }

  template< typename T, typename Compare >
  void RBTree< T, Compare >::setColor(Tree< T, Compare > * node, char color)
  {
    node->color_ = color;
  }

  template< typename T, typename Compare >
  bool RBTree< T, Compare >::isRed(const Tree< T, Compare > * node)
  {
    return node->color_ == 'r';
  }

  template< typename T, typename Compare >
  bool RBTree< T, Compare >::isBlack(const Tree< T, Compare > * node)
  {
    return node->color_ == 'b';
  }

  template< typename T, typename Compare >
  bool operator==(const RBTree< T, Compare > & lhs, const RBTree< T, Compare > & rhs)
  {
    return lhs.isEqual(rhs);
  }

  template< typename T, typename Compare >
  bool operator!=(const RBTree< T, Compare > & lhs, const RBTree< T, Compare > & rhs)
  {
    return !(lhs == rhs);
  }
}

#endif
