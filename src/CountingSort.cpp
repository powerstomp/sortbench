#include "CountingSort.h"

#include <algorithm>
#include <utility>

void Sort::Counting::Apply(int *data, int size)
{
    int max = 0;
    for (int i = 0; i < size; ++i)
        if (data[i] > max)
            max = data[i];

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

long long Sort::Counting::CountComparisons(int *data, int size)
{
    long long count = 0;
    int max = 0;
    for (int i = 0; ++count && i < size; ++i)
        if (++count && data[i] > max)
            max = data[i];

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