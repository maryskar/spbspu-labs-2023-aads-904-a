#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include "AVLTree.h"
#include "StreamProcessingS2.h"
#include "printMessages.h"
#include "ExprProcessFunctions.h"

namespace
{
  class sumKeys
  {
  public:
    sumKeys();
    void operator()(const std::pair< int, std::string >&);
    long long getSum() const;
  private:
    long long sum_;
  };
  class sumValues
  {
  public:
    void operator()(const std::pair< int, std::string >&);
    const std::string& getString() const;
  private:
    std::string str_;
  };
  class sumKeysAndValues
  {
  public:
    void operator()(const std::pair< int, std::string >&);
    std::string getResult() const;
  private:
    sumKeys sum_;
    sumValues values_;
  };
  using Tree = skarlygina::AVLTree< int, std::string >;
  Tree getTree(std::istream&);
}

int main(int argc, char** argv)
{
  if (argc != 3)
  {
    skarlygina::printBadNumberOfArgs(std::cerr);
    return 1;
  }
  std::fstream in(argv[2]);
  if (!in.good())
  {
    skarlygina::printUnableToReadFile(std::cerr);
    return 1;
  }
  try
  {
    auto tree = getTree(in);
    if (tree.isEmpty())
    {
      skarlygina::printEmpty(std::cout);
      return 0;
    }
    sumKeysAndValues result;
    std::string wayOfTraverse = argv[1];
    if (wayOfTraverse == "ascending")
    {
      result = tree.traverse_lnr(result);
    }
    else if (wayOfTraverse == "descending")
    {
      result = tree.traverse_rnl(result);
    }
    else if (wayOfTraverse == "breadth")
    {
      result = tree.traverse_breadth(result);
    }
    else
    {
      throw std::invalid_argument("Unknown way of traverse");
    }
    std::cout << result.getResult() << std::endl;
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << std::endl;
    return 2;
  }
  return 0;
}

namespace
{
  sumKeys::sumKeys():
    sum_(0)
  {}
  void sumKeys::operator()(const std::pair< int, std::string >& node)
  {
    sum_ = skarlygina::sum(sum_, node.first);
  }
  long long sumKeys::getSum() const
  {
    return sum_;
  }
  void sumValues::operator()(const std::pair< int, std::string >& node)
  {
    if (!str_.empty())
    {
      str_ += ' ';
    }
    str_ += node.second;
  }
  const std::string& sumValues::getString() const
  {
    return str_;
  }
  void sumKeysAndValues::operator()(const std::pair< int, std::string >& node)
  {
    sum_(node);
    values_(node);
  }
  std::string sumKeysAndValues::getResult() const
  {
    return std::to_string(sum_.getSum()) + ' ' + values_.getString();
  }
  Tree getTree(std::istream& in)
  {
    auto words = skarlygina::getWords(in, '\n');
    Tree returnable;
    int key = 0;
    std::string value;
    for (auto i = words.cbegin(); i != words.cend(); ++i)
    {
      key = std::stoi(*i);
      ++i;
      value = *i;
      returnable.insert(key, value);
    }
    return returnable;
  }
}

