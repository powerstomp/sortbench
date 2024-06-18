#include "CountingSort.h"

#include <algorithm>
#include <utility>

void Sort::Counting::Apply(int *data, int size)
{
    int max = *std::max_element(data, data + size);
    int *count = new int[max + 1]();
    for (int i = 0; i < size; ++i)
        ++count[data[i]];

    for (int i = 1; i <= max; ++i)
        count[i] += count[i - 1];

    int *temp = new int[size];
    for (int i = size - 1; i >= 0; --i)
        temp[--count[data[i]]] = data[i];

    for (int i = 0; i < size; ++i)
        data[i] = temp[i];

    delete[] count;
    delete[] temp;
}

int Sort::Counting::CountComparisons(int *data, int size)
{
    int count = 0;
    int max = *std::max_element(data, data + size);
    int *countArray = new int[max + 1]();
    for (int i = 0; ++count && i < size; ++i)
        ++countArray[data[i]];

    for (int i = 1; ++count && i <= max; ++i)
        countArray[i] += countArray[i - 1];

    int *temp = new int[size];
    for (int i = size - 1; ++count && i >= 0; --i)
        temp[--countArray[data[i]]] = data[i];

    for (int i = 0; ++count && i < size; ++i)
        data[i] = temp[i];

    delete[] countArray;
    delete[] temp;
    return count;
}