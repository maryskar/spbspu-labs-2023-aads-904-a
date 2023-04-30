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
      using node_type = NodeOfTwoThreeTree<Key, Value, Compare>;
      Key *key;
      Value *value;
      unsigned size;
      node_type *first;
      node_type *second;
      node_type *third;
      node_type *fourth;
      node_type *parent;
      NodeOfTwoThreeTree() :
        key(static_cast< Key * >(::operator new[](sizeof(Key) * 3))),
        value(static_cast< Value * >(::operator new[](sizeof(Value) * 3))),
        size(0),
        first(nullptr),
        second(nullptr),
        third(nullptr),
        fourth(nullptr),
        parent(nullptr),
        compare_(Compare())
      {
      }
      NodeOfTwoThreeTree(const Key &k, const Value &v) :
        key(static_cast< Key * >(::operator new[](sizeof(Key) * 3))),
        value(static_cast< Value * >(::operator new[](sizeof(Value) * 3))),
        size(1),
        first(nullptr),
        second(nullptr),
        third(nullptr),
        fourth(nullptr),
        parent(nullptr),
        compare_(Compare())
      {
        key[0] = key;
        value[0] = value;
      }
      NodeOfTwoThreeTree(const Key &k, const Value &v, node_type *fi, node_type *s, node_type *t, node_type *fo,
                         node_type *p) :
        key(static_cast< Key * >(::operator new[](sizeof(Key) * 3))),
        value(static_cast< Value * >(::operator new[](sizeof(Value) * 3))),
        size(1),
        first(fi),
        second(s),
        third(t),
        fourth(fo),
        parent(p),
        compare_(Compare())
      {
        key[0] = key;
        value[0] = value;
      }
      ~NodeOfTwoThreeTree()
      {
        ::operator delete[](key);
        ::operator delete[](value);
      }
      bool isList() const
      {
        return (first == nullptr) && (second == nullptr) && (third == nullptr);
      }
      void insert(const Key &k, const Value &v)
      {
        key[size] = k;
        value[size] = v;
        size++;
        sort();
      }
      void becomeNode2(const Key &k, const Value &v, node_type *first_, node_type *second_)
      {
        key[0] = k;
        value[0] = v;
        first = first_;
        second = second_;
        third = nullptr;
        fourth = nullptr;
        parent = nullptr;
        size = 1;
      }
      node_type *getLastChildren()
      {
        return (third) ? third : (second) ? second : first;
      }
      bool contains(const Key &k)
      {
        for (unsigned int i = 0; i < size; ++i)
        {
          if (key[i] == k)
          {
            return true;
          }
        }
        return false;
      }
      void removeFromNode(Key k)
      {
        if (size >= 1 && key[0] == k)
        {
          key[0] = key[1];
          key[1] = key[2];
          size--;
        }
        else if (size == 2 && key[1] == k)
        {
          key[1] = key[2];
          size--;
        }
      }
    private:
      Compare compare_;
      void sort()
      {
        if (!compare_(key[0], key[1]))
        {
          std::swap(key[0], key[1]);
          std::swap(value[0], value[1]);
        }
        if (size == 3)
        {
          if (!compare_(key[0], key[2]))
          {
            std::swap(key[0], key[2]);
            std::swap(value[0], value[2]);
          }
          if (!compare_(key[1], key[2]))
          {
            std::swap(key[1], key[2]);
            std::swap(value[1], value[2]);
          }
        }
      }
    };
  }
}
#endif
