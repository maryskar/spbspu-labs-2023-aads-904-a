#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <iostream> 
#include <string>

struct Node
{
  std::string key_;
  Node* next;
  size_t frequency_;

  Node() :
    key_(""), frequency_(0), next(nullptr)
  {}
  Node(std::string key, size_t frequency) :
    key_(key), frequency_(frequency), next(nullptr)
  {}
};

class LinkedList
{
private:
  Node* head;
  size_t length;

public:
  LinkedList();
  ~LinkedList();
  Node* getHead();
  void insert(Node* key);
  bool remove(std::string key);
  Node* getItem(std::string key);
  void print();
  size_t getLength();
  void incrementValue() { length++; }
};
#endif
