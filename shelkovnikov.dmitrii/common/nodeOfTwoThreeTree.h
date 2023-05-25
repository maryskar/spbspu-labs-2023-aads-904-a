#ifndef SPBSPU_LABS_2023_AADS_904_A_NODEOFTWOTHREETREE_H
#define SPBSPU_LABS_2023_AADS_904_A_NODEOFTWOTHREETREE_H
#include <algorithm>
namespace dimkashelk
{
  namespace details
  {
    template < typename Key, typename Value, typename Compare >
    struct NodeOfTwoThreeTree
    {
    public:
      using node_type = NodeOfTwoThreeTree< Key, Value, Compare >;
      std::pair< Key, Value > data[3];
      unsigned size;
      node_type *first;
      node_type *second;
      node_type *third;
      node_type *fourth;
      node_type *parent;
      NodeOfTwoThreeTree():
        data(),
        size(0),
        first(nullptr),
        second(nullptr),
        third(nullptr),
        fourth(nullptr),
        parent(nullptr),
        compare_(Compare())
      {}
      NodeOfTwoThreeTree(const Key &k, const Value &v):
        data{{k, v}, {Key(), Value()}, {Key(), Value()}},
        size(1),
        first(nullptr),
        second(nullptr),
        third(nullptr),
        fourth(nullptr),
        parent(nullptr),
        compare_(Compare())
      {}
      NodeOfTwoThreeTree(const Key &k, const Value &v, node_type *fi, node_type *s, node_type *t, node_type *fo, node_type *p):
        data{{k, v}, {Key(), Value()}, {Key(), Value()}},
        size(1),
        first(fi),
        second(s),
        third(t),
        fourth(fo),
        parent(p),
        compare_(Compare())
      {}
      bool isList() const
      {
        return (first == nullptr) && (second == nullptr) && (third == nullptr);
      }
      void insert(const Key &k, const Value &v)
      {
        data[size] = {k, v};
        size++;
        sort();
      }
      void becomeNode2(const Key &k, const Value &v, node_type *first_, node_type *second_)
      {
        data[0] = {k, v};
        first = first_;
        second = second_;
        third = nullptr;
        fourth = nullptr;
        parent = nullptr;
        size = 1;
      }
      node_type *getLastChildren()
      {
        return (third)? third: (second)? second: first;
      }
      bool contains(const Key &k)
      {
        for (unsigned int i = 0; i < size; ++i)
        {
          if (data[i].first == k)
          {
            return true;
          }
        }
        return false;
      }
      void removeFromNode(Key k)
      {
        if (size >= 1 && data[0].first == k)
        {
          data[0] = data[1];
          data[1] = data[2];
          size--;
        }
        else if (size == 2 && data[1].first == k)
        {
          data[1] = data[2];
          size--;
        }
      }
    private:
      Compare compare_;
      void sort()
      {
        if (!compare_(data[0].first, data[1].first))
        {
          std::swap(data[0], data[1]);
        }
        if (size == 3)
        {
          if (!compare_(data[0].first, data[2].first))
          {
            std::swap(data[0], data[2]);
          }
          if (!compare_(data[1].first, data[2].first))
          {
            std::swap(data[1], data[2]);
          }
        }
      }
    };
  }
}
#endif
