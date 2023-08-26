#include <iostream>
#include <deque>
#include <algorithm>
#include <random>
#include "insertion.hpp"
#include "oddeven.hpp"

int main()
{
    std::deque<int> data = {5, 2, 9, 1, 5, 6, 3, 8, 7, 4};

    std::cout << "Original data: ";
    for (const auto& num : data)
    {
        std::cout << num << " ";
    }
    std::cout << "\n";

    auto insertion_data = data;
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

    return 0;
}
