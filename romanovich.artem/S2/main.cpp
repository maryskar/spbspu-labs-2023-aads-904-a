/*
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "dict.h"
void
printDictionary(const Dictionary< std::string, Dictionary< int, std::string > > &dictionary)
{
  for (const auto &entry: dictionary)
  {
    std::cout << "Dictionary name: " << entry.first << "\n";
    const auto &dictData = entry.second;
    for (const auto &item: dictData)
    {
      std::cout << "Key: " << item.first << ", Value: " << item.second << "\n";
    }
    std::cout << "\n";
  }
}
void splitString(std::vector< std::string > &elems, const std::string &line, char del)
{
  std::string word;
  size_t startPos = 0;
  size_t endPos = line.find(del);
  while (endPos != std::string::npos)
  {
    word = line.substr(startPos, endPos - startPos);
    elems.push_back(word);
    startPos = endPos + 1;
    endPos = line.find(del, startPos);
  }
  word = line.substr(startPos, endPos);
  elems.push_back(word);
}
int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cerr << "No file provided.\n";
    return 1;
  }
  std::ifstream input(argv[1]);
  if (!input)
  {
    std::cerr << "Cannot open file.\n";
    return 1;
  }
  using dict_type = Dictionary< int, std::string >;
  using dict_value_type = std::pair< int, std::string >;
  using container_type = Dictionary< std::string, dict_type >;
  using container_value_type = std::pair< std::string, dict_type >;
  container_type dictionary;
  std::string line;
  while (std::getline(input, line))
  {
    std::vector< std::string > lineWords;
    splitString(lineWords, line, ' ');
    std::string dictName = lineWords[0];
    dict_type dictData;
    for (size_t i = 1; i < lineWords.size(); i += 2)
    {
      int key = std::stoi(lineWords[i]);
      std::string val = lineWords[i + 1];
      //std::cout << key << " " << val << "\n";
      dictData.emplace(dict_value_type(key, val));
      auto ptr = dictData.data_.begin_;
      while (ptr)
      {
        std::cout << ptr->data_.first << ' '
                  << ptr->data_.second << ' ';
        ptr = ptr->next_;
      }
      //std::cout << '\n';
    }
    dictionary.emplace(container_value_type(dictName, dictData));
    //printDictionary(dictionary);
    //std::cout << "\n";
  }
  printDictionary(dictionary);
  */
/*std::cout << "@";
  std::cout << sizeof dictionary.data_.begin_->data_;
  std::cout << "@";
  auto ptr = pt.second.data_.begin_;
 while (ptr)
 {
   std::cout << ptr->data_.second << ' ';
   std::cout << ptr->data_.first;
   ptr = ptr->next_;
 }*//*

}
*/
//----------------------------------------
#include <iostream>
#include "forwardlist.h"

int main() {
  ForwardList<int> myList;

  // Добавление элементов в начало списка
  myList.push_front(1);
  myList.push_front(2);
  myList.push_front(3);

  // Перебор элементов с помощью итераторов
  std::cout << "Список: ";
  for (const auto& value : myList) {
    std::cout << value << " ";
  }
  std::cout << std::endl;

  // Проверка на пустоту списка
  std::cout << "Список пуст: " << std::boolalpha << myList.empty() << std::endl;

  // Вставка элемента после указанной позиции
  ForwardList<int>::const_iterator it = myList.cbegin();
  ++it; // Переходим ко второму элементу
  myList.insert_after(it, 10); // Вставляем число 10 после второго элемента

  // Вывод списка после вставки элемента
  std::cout << "Список после вставки: ";
  for (const auto& value : myList) {
    std::cout << value << " ";
  }
  std::cout << std::endl;

  // Удаление элемента после указанной позиции
  myList.erase_after(it);

  // Вывод списка после удаления элемента
  std::cout << "Список после удаления: ";
  for (const auto& value : myList) {
    std::cout << value << " ";
  }
  std::cout << std::endl;

  // Изменение размера списка
  myList.resize(5, 0); // Увеличиваем размер списка до 5 и заполняем новые элементы нулями

  // Вывод списка после изменения размера
  std::cout << "Список после изменения размера: ";
  for (const auto& value : myList) {
    std::cout << value << " ";
  }
  std::cout << std::endl;

  // Изменение размера списка и заполнение новых элементов пользовательским значением
  myList.resize(3, 100); // Уменьшаем размер списка до 3 и заполняем новые элементы значением 100

  // Вывод списка после изменения размера
  std::cout << "Список после изменения размера и заполнения пользовательским значением: ";
  for (const auto& value : myList) {
    std::cout << value << " ";
  }
  std::cout << std::endl;

  // Перестановка элементов списка в обратном порядке
  myList.reverse();

  // Вывод списка после перестановки элементов
  std::cout << "Список после перестановки в обратном порядке: ";
  for (const auto& value : myList) {
    std::cout << value << " ";
  }
  std::cout << std::endl;

  // Удаление всех элементов списка
  myList.clear();

  // Проверка на пустоту списка после удаления
  std::cout << "Список пуст: " << std::boolalpha << myList.empty() << std::endl;

  // Вставка элемента после указанной позиции с помощью emplace_after()
  ForwardList<int>::const_iterator it1 = myList.cbegin();
  ++it1; // Переходим ко второму элементу
  myList.emplace_after(it1, 10); // Вставляем число 10 после второго элемента с помощью emplace_after()

  // Вывод списка после вставки элемента
  std::cout << "Список после вставки: ";
  for (const auto& value : myList) {
    std::cout << value << " ";
  }
  std::cout << std::endl;

  // Удаление первого элемента списка с помощью pop_front()
  myList.pop_front();

  // Вывод списка после удаления элемента
  std::cout << "Список после удаления: ";
  for (const auto& value : myList) {
    std::cout << value << " ";
  }
  std::cout << std::endl;

  return 0;
}
