#ifndef FORWARDLIST_H
#define FORWARDLIST_H
#include <cstddef>
#include <stdexcept>
#include "ForwardIter.h"
#include "ForwardConstIter.h"
#include "../common/List.h"
namespace timofeev
{
  template<typename T>
  class ForwardList
  {
  public:
    using iter = ForwardIterator<T>;
    using constIter = ForwardConstIterator<T>;
    ForwardList();
    ~ForwardList();
    ForwardList(const ForwardList<T> &lhs);
    ForwardList(ForwardList<T> &&rhs) noexcept;

    ForwardList<T> &operator=(const ForwardList<T> &rhs);
    ForwardList<T> &operator=(ForwardList<T> &&rhs) noexcept;

    bool empty() const;
    void clear();
    iter before_begin() noexcept;
    constIter before_begin() const noexcept;
    iter begin() noexcept;
    constIter begin() const noexcept;
    iter end() noexcept;
    constIter end() const noexcept;
    constIter cbegin() const noexcept;
    constIter cend() const noexcept;
    constIter cbefore_begin() const noexcept;

    iter insert_after(constIter pos, const T &value);
    iter insert_after(constIter pos, T &&value);
    iter insert_after(constIter pos, size_t count, const T &value);
    iter insert_after(constIter pos, iter first, iter last);

    T &front();
    iter erase_after(constIter pos);
    iter erase_after(constIter first, constIter last);
    template<typename ...Args>
    iter emplace_after(constIter pos, Args &&...args);
    iter emplace_front(constIter pos);

    void push_front(const T &value);
    void push_front(T &&value);
    void pop_front();

    void swap(ForwardList<T> &other) noexcept;

    void splice_after(constIter pos, ForwardList<T> &other);
    void splice_after(constIter pos, ForwardList<T> &&other);

    void remove(const T &value);
    template<typename Comparator>
    void remove_if(Comparator p);

    size_t size() const noexcept;

  private:
    List<T> *fakenode_;
    List<T> *tail_;
    size_t size_;
  };
}