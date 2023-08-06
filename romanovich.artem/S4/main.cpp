#include <iostream>
#include <random>
#include <ctime>
#include "redblack_tree.h"
void fillArrayWithRandomNumbers(int arr[], int size, int minValue, int maxValue)
{
  std::srand(static_cast<unsigned int>(std::time(nullptr)));
  for (int i = 0; i < size; ++i)
  {
    arr[i] = std::rand() % (maxValue - minValue + 1) + minValue;
  }
}
void insertAndPrint(romanovich::RedBlackTree< int, int, std::less<> > &rbTree, int i)
{
  rbTree.insert({i,  i});
  rbTree.rotBst_.printNode(rbTree.rotBst_.bst_.root_, false, "");
  std::cout << "-------------\n";
}
int main()
{
  // Создаем красно-черное дерево для целых чисел
  romanovich::RedBlackTree< int, int, std::less<> > rbTree;
//  insertAndPrint(rbTree, 24);
//  insertAndPrint(rbTree, 5);
//  insertAndPrint(rbTree, 1);

  const int arraySize = 10;
  int myArray[arraySize];
  int minValue = 1;
  int maxValue = 20;
  fillArrayWithRandomNumbers(myArray, arraySize, minValue, maxValue);

  // Выводим сгенерированный массив
  for (int i: myArray)
  {
    insertAndPrint(rbTree, i);
  }

// Выводим элементы дерева в возрастающем порядке
  for (const auto &node: rbTree)
  {
    std::cout << "Key: " << node.first << ", Value: " << node.second << std::endl;
  }
  return 0;
}
