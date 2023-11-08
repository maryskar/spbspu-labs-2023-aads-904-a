#include <iostream>
#include <functional>
#include <deque>
#include <iomanip>
#include "BidirectionalList.h"
#include "ForwardList.h"
#include "printMessages.h"
#include "Sorts.h"

namespace
{
  template < typename T, typename NumGenerator >
  struct fillWithRands
  {
    void operator()(size_t size)
    {
      NumGenerator numGener;
      for (size_t i = 0; i < size; ++i)
      {
        auto num = numGener();
        fwdList_.pushBack(num);
        bidirList_.pushBack(num);
        deque_.push_back(num);
      }
    }
    skarlygina::ForwardList< T > fwdList_;
    skarlygina::BidirectionalList< T > bidirList_;
    std::deque< T > deque_;
  };
  struct generateInt
  {
    int operator()()
    {
      return (std::rand() % 100);
    }
  };
  struct generateFloat
  {
    float operator()()
    {
      return static_cast< float >(std::rand() % 100) / 100;
    }
  };
  template < typename Container >
  std::ostream& printValues(std::ostream& out, const Container& container)
  {
    if (container.cbegin() == container.cend())
    {
      return out;
    }
    out << *container.cbegin();
    for (auto i = (++container.cbegin()); i != container.cend(); ++i)
    {
      out << ' ' << *i;
    }
    out << '\n';
    return out;
  }
  template < typename T, typename Compare >
  class Sorter
  {
  public:
    Sorter(skarlygina::ForwardList< T >& fwdList, skarlygina::BidirectionalList< T >& bidirList, std::deque< T >& deque):
      fwdListForBubbleSort_(std::move(fwdList)),
      bidirListForBubbleSort_(std::move(bidirList)),
      dequeForBubbleSort_(std::move(deque)),
      bidirListForQsort_(bidirListForBubbleSort_),
      dequeForQsort_(dequeForBubbleSort_),
      dequeForBucketSort_(dequeForBubbleSort_)
    {}
    void operator()(const Compare& cmp)
    {
      using dequeIt = typename std::deque< T >::iterator;
      using bidirIt = skarlygina::BiIterator< T >;
      using Strategy = skarlygina::twoBuckets< dequeIt >;
      using fwdIt = skarlygina::Iterator< T >;
      skarlygina::bubbleSort< fwdIt, Compare >(fwdListForBubbleSort_.begin(), fwdListForBubbleSort_.end(), cmp);
      skarlygina::bubbleSort< bidirIt, Compare >(bidirListForBubbleSort_.begin(), bidirListForBubbleSort_.end(), cmp);
      skarlygina::bubbleSort< dequeIt, Compare >(dequeForBubbleSort_.begin(), dequeForBubbleSort_.end(), cmp);
      skarlygina::qsort< bidirIt, Compare >(bidirListForQsort_.begin(), bidirListForQsort_.end(), cmp);
      skarlygina::qsort< dequeIt, Compare >(dequeForQsort_.begin(), dequeForQsort_.end(), cmp);
      Strategy strategy(dequeForBucketSort_.begin(), dequeForBucketSort_.end());
      skarlygina::bucketSort< dequeIt, Compare, Strategy >(dequeForBucketSort_.begin(), dequeForBucketSort_.end(), cmp, strategy);
    }
    std::ostream& printResults(std::ostream& out) const
    {
      printValues(out, fwdListForBubbleSort_);
      printValues(out, bidirListForBubbleSort_);
      printValues(out, dequeForBubbleSort_);
      printValues(out, bidirListForQsort_);
      printValues(out, dequeForQsort_);
      printValues(out, dequeForBucketSort_);
      return out;
    }
  private:
    skarlygina::ForwardList< T > fwdListForBubbleSort_;
    skarlygina::BidirectionalList< T > bidirListForBubbleSort_;
    std::deque< T > dequeForBubbleSort_;
    skarlygina::BidirectionalList< T > bidirListForQsort_;
    std::deque< T > dequeForQsort_;
    std::deque< T > dequeForBucketSort_;
  };
  template < typename T, typename NumGenerator, typename Compare >
  void sortAndPrint(std::ostream& out, size_t size, const Compare& cmp)
  {
    fillWithRands< T, NumGenerator > data;
    data(size);
    printValues(out, data.fwdList_);
    Sorter< T, Compare > sorter(data.fwdList_, data.bidirList_, data.deque_);
    sorter(cmp);
    sorter.printResults(out);
  }
}

int main(int argc, char** argv)
{
  if (argc != 4)
  {
    skarlygina::printBadNumberOfArgs(std::cerr);
    return 1;
  }
    try
    {
    int size = std::stoi(argv[3]);
    if (size <= 0)
    {
      throw std::invalid_argument("Bad number of args");
    }
    std::string order = argv[1];
    std::string type = argv[2];
    if ((order == "ascending") && (type == "ints"))
    {
      sortAndPrint< int, generateInt, std::less< int > >(std::cout, size, std::less< int >());
    }
    else if ((order == "ascending") && (type == "floats"))
    {
      sortAndPrint< float, generateFloat, std::less< float > >(std::cout, size, std::less< float >());
    }
    else if ((order == "descending") && (type == "ints"))
    {
      sortAndPrint< int, generateInt, std::greater< int > >(std::cout, size, std::greater< int >());
    }
    else if ((order == "descending") && (type == "floats"))
    {
      sortAndPrint< float, generateFloat, std::greater< float > >(std::cout, size, std::greater< float >());
    }
    else
    {
      throw std::logic_error("Bad args");
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << std::endl;
    return 2;
  }
  return 0;
}



