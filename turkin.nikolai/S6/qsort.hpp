#ifndef QSORT_HPP
#define QSORT_HPP

#include <utility>
#include <iterator>

namespace
{
  template< typename T, typename UnaryPred >
  struct Lcompare
  {
    public:
      explicit Lcompare(const T & src):
        src_(src)
      {}

      bool operator()(const T & lhs)
      {
        return p_(lhs, src_);
      }

    private:
      T src_;
      UnaryPred p_;
  };

  template< typename T, typename UnaryPred >
  struct Bcompare
  {
  public:
    explicit Bcompare(const T & src):
        src_(src)
      {}

    bool operator()(const T & rhs)
      {
      return !p_(src_, rhs);
    }

  private:
    T src_;
    UnaryPred p_;
  };

  template< typename ForwardIt, typename UnaryPred >
  ForwardIt partition(ForwardIt first, ForwardIt last, UnaryPred p)
  {
    while (first != last && p(*first))
    {
      ++first;
    }
    if (first == last)
    {
      return first;
    }
    for (auto i = std::next(first); i != last; ++i)
    {
      if (p(*i))
      {
        std::swap(*i, *first);
        ++first;
      }
    }
    return first;
  }
}

namespace turkin
{
  template< typename ForwardIt, typename UnaryPred >
  void qsort(ForwardIt begin, ForwardIt last, UnaryPred p)
  {
    if (std::distance(begin, last) < 2)
    {
      return;
    }
    auto pivot = *std::next(begin, std::distance(begin, last) / 2);
    auto l = partition(begin, last, Lcompare< decltype(pivot), UnaryPred >(pivot));
    auto b = partition(begin, last, Bcompare< decltype(pivot), UnaryPred >(pivot));
    qsort(begin, l, p);
    qsort(b, last, p);
  }
}

#endif
