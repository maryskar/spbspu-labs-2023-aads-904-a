#include <iostream>
#include <deque>
#include <algorithm>
#include <random>
#include "insertion.hpp"

int main()
{
    std::deque<int> data = {5, 2, 9, 1, 5, 6, 3, 8, 7, 4};

    std::cout << "Original data: ";
    for (const auto& num : data)
    {
        std::cout << num << " ";
    }
    std::cout << "\n";

    auto insertionData = data;
    insertionSort(insertionData.begin(), insertionData.end());
    std::cout << "Insertion Sort: ";
    for (const auto& num : insertionData)
    {
        std::cout << num << " ";
    }
    std::cout << "\n";

    return 0;
}
