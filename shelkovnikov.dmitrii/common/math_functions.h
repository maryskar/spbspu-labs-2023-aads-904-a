#ifndef SPBSPU_LABS_2023_AADS_904_A_MATH_FUNCTIONS_H
#define SPBSPU_LABS_2023_AADS_904_A_MATH_FUNCTIONS_H
namespace dimkashelk
{
  namespace details
  {
    template < typename K, typename Comp >
    bool isEqual(const K &key1, const K &key2)
    {
      return !Comp{}(key1, key2) && !Comp{}(key2, key1);
    }
    template < typename K, typename Comp >
    bool isNotEqual(const K &key1, const K &key2)
    {
      return !isEqual< K, Comp >(key1, key2);
    }
  }
}
#endif
