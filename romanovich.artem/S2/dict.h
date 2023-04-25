#ifndef DICT_H
#define DICT_H
template < typename Key, typename Value, typename Compare >
class Dictionary
{
public:
  Dictionary();
  void push(Key k, Value v);
  Value get(Key k);
  Value drop(Key k);
private:
  Key key_;
  Value value_;
};
template < typename Key, typename Value, typename Compare >
Dictionary < Key, Value, Compare >::Dictionary():
key_(),
v
{
}
template < typename Key, typename Value, typename Compare >
Value Dictionary < Key, Value, Compare >::drop(Key k)
{
  return nullptr;
}
template < typename Key, typename Value, typename Compare >
Value Dictionary < Key, Value, Compare >::get(Key k)
{
  return nullptr;
}
template < typename Key, typename Value, typename Compare >
void Dictionary < Key, Value, Compare >::push(Key k, Value v)
{
}
#endif
