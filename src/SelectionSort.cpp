#include "SelectionSort.h"

#include <utility>

void Sort::Selection::Apply(int *data, int n)
{
    int min;
    for (int i = 0; i < n - 1; ++i)
    {
        min = i;
        for (int j = i + 1; j < n; ++j)
            if (data[j] < data[min])
                min = j;
        if (min != i)
            std::swap(data[i], data[min]);
    }
}

int Sort::Selection::CountComparisons(int *data, int n)
{
    int count = 0, min;
    for (int i = 0; ++count && i < n - 1; i++)
    {
        min = i;
        for (int j = i + 1; ++count && j < n; j++)
        {
            if (++count && data[j] < data[min])
                min = j;
        }
        if (++count && min != i)
            std::swap(data[i], data[min]);
    }
    return count;
}