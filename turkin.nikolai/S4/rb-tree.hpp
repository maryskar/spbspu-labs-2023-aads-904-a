#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include <utility>
#include "iterators/direct-iterator.hpp"
#include "iterators/direct-const-iterator.hpp"
#include "iterators/reverse-iterator.hpp"
#include "iterators/reverse-const-iterator.hpp"
#include "tree-node.hpp"

namespace turkin
{
  template< typename K, typename V, typename C >
  class RBtree
  {
    using tree = RBtree< K, V, C >;
    using tree_t = std::pair< K, V >;
    using dit = DirectIterator< K, V, C >;
    using dcit = DirectConstIterator< K, V, C >;
    using rit = ReverseIterator< K, V, C >;
    using crit = ReverseConstIterator< K, V, C >;
    public:
      RBtree();
      RBtree(const tree & rhs);
      RBtree(tree && rhs);
      tree operator=(const tree & rhs);
      tree operator=(tree && rhs);
      ~RBtree();
      
      dit before_begin() noexcept;
      dcit before_begin() const noexcept;
      dcit cbefore_begin() const noexcept;
      dit begin() noexcept;
      dcit begin() const noexcept;
      dcit cbegin() const noexcept;
      dit end() noexcept;
      dcit end() const noexcept;
      dcit cend() const noexcept;
      dit rbegin() noexcept;
      dcit rbegin() const noexcept;
      dcit crbegin() const noexcept;
      dit rend() noexcept;
      dcit rend() const noexcept;
      dcit crend() const noexcept;

      bool empty() const noexcept;
      std::size_t size() const noexcept;

      void clear() noexcept;
      std::pair< dit, bool > insert(const K & k, const V & v);
      std::pair< dit, bool > insert(const tree_t & value);
      template< class... Args >
      std::pair< dit, bool > emplace(Args &&... args);
      dit erase_after(dcit pos);
      dit erase_after(dcit first, dcit last);
      std::size_t erase(const K & k);
      void swap(tree & rhs) noexcept;
      tree_t extract_after(dcit pos);
      V at(const K & k);
      const V at(const K & k) const;

      std::size_t count(const K & k) const;
      dit find(const K & k);
      dcit find(const K & k) const;
      std::pair< dit, dit > equal_range(const K & k);
      std::pair< dcit, dcit > equal_range(const K & k) const;
      dit lower_bound(const K & k);
      dcit lower_bound(const K & k) const;
      dit upper_bound(const K & k);
      dcit upper_bound(const K & k) const;
      
    private:
      TreeNode< tree_t, C > source_;
      C cmp_;
  };
}

#endif
