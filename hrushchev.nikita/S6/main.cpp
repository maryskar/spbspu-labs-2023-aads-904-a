#include <iostream>
#include <deque>
#include <list>
#include <algorithm>
#include <random>
#include "insertion.hpp"
#include "oddeven.hpp"
#include "shaker.hpp"
#include <forwardlist.hpp>

int main()
{
    std::deque< int > data = {5, 2, 9, 1, 5, 6, 3, 8, 7, 4};

    hrushchev::ForwardList < int > my_list;
    my_list.push_front(1);
    my_list.push_front(13);
    my_list.push_front(51);
    my_list.push_front(15);
    my_list.push_front(71);
    my_list.push_front(11);
    std::deque< int > data2(my_list.begin(), my_list.end());
    std::cout << "Original data: ";
    for (const auto& num : data)
    {
        std::cout << num << " ";
    }
    std::cout << "\n";

    auto insertion_data = data2;
    insertionSort(insertion_data.begin(), insertion_data.end());
    std::cout << "Insertion Sort: ";
    for (const auto& num : insertion_data)
    {
        std::cout << num << " ";
    }
    std::cout << "\n";

    auto odd_even_data = data;
    oddEvenSort(odd_even_data.begin(), odd_even_data.end());
    std::cout << "OddEven Sort: ";
    for (const auto& num : odd_even_data)
    {
        std::cout << num << " ";
    }
    std::cout << "\n";

    auto shaker_data = data;
    shakerSort(shaker_data.begin(), shaker_data.end());
    std::cout << "Shaker Sort: ";
    for (const auto& num : shaker_data)
    {
        std::cout << num << " ";
    }
    std::cout << "\n";

    auto odd_even_list = my_list;
    oddEvenSort(odd_even_list.begin(), odd_even_list.end());
    std::cout << "OddEven Sort: ";
    for (const auto& num : odd_even_list)
    {
        std::cout << num << " ";
    }
    std::cout << "\n";
}
