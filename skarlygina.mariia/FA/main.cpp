#include "hash_table.h"
#include <iostream>
/* –азработать и реализовать алгоритм формировани€ частотного словар€ :
    Х определить пон€тие слово,
    Х прочитать текст и сформировать набор слов вместе с информацией о частоте их
    встречаемости
    Х определить три чаще всего встречающихс€ слова
    ƒл€ реализации задани€ использовать хеш - таблицу с разрешением коллизий с помощью
    цепочек.
     лючом хеш - функции должно быть слово.
*/
int main()
{
  HashTable hash_table;
  hash_table.insertFromFile("text.txt");
  hash_table.insertFromFile("text1.txt"); //проверка передачи несуществующего файла

  hash_table.printWordFrequencies();

  size_t itemCount = hash_table.getNumberofItems();

  std::cout << "Number of items in the hash table: " << itemCount << std::endl;

  hash_table.printTopWords(3);

  return 0;
}