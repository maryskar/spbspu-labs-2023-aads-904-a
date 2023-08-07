#ifndef MAP_H
#define MAP_H
#include <functional>
#include "redblack_tree.h"
namespace romanovich
{
  template< typename Key, typename Value, typename Compare = std::less<> >
  class Map
  {
  public:
    using data_t = std::pair< const Key, Value >;
    using iterator = typename RedBlackTree< Key, Value, Compare >::iterator;
    using const_iterator = typename RedBlackTree< Key, Value, Compare >::const_iterator;
    Map();
    Map(const Map &other) = default;
    Map(Map &&other) noexcept;
    explicit Map(const Key &comp);
    template< typename InputIt >
    Map(InputIt first, InputIt last, const Key &comp = Key());
    Map(std::initializer_list< data_t > init, const Key &comp = Key());
    ~Map() = default;
    Map &operator=(const Map &other);
    Map &operator=(Map &&other) noexcept;
    Map &operator=(std::initializer_list< data_t > init);
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
    std::pair< iterator, bool > insert(const data_t &value);
    template< typename P >
    std::pair< iterator, bool > insert(P &&value);
    iterator insert(const_iterator pos, const data_t &value);
    template< typename P >
    iterator insert(const_iterator pos, P &&value);
    template< typename InputIt >
    void insert(InputIt first, InputIt last);
    void insert(std::initializer_list< data_t > init);
    template< typename... Args >
    std::pair< iterator, bool > emplace(Args &&... args);
    template< typename... Args >
    iterator emplace_hint(const_iterator hint, Args &&... args);
    Value &at(const Key &key);
    const Value &at(const Key &key) const;
    Value &operator[](const Key &key);
    Value &operator[](Key &&key);
    iterator erase(iterator pos);
    iterator erase(const_iterator pos);
    iterator erase(const_iterator first, const_iterator last);
    size_t erase(const Key &key);
    void swap(Map &other);
    size_t count(const Key &key) const;
    iterator find(const Key &key);
    const_iterator find(const Key &key) const;
    std::pair< iterator, iterator > equal_range(const Key &key);
    std::pair< const_iterator, const_iterator > equal_range(const Key &key) const;
    iterator lower_bound(const Key &key);
    const_iterator lower_bound(const Key &key) const;
    iterator upper_bound(const Key &key);
    const_iterator upper_bound(const Key &key) const;
    Key key_comp() const;
    bool equal(const Map &rhs) const;
  private:
    RedBlackTree< Key, Value, Compare > rbBst;
    Compare compare_;
  };
}
#endif
