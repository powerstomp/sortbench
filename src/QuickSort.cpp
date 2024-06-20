#include "QuickSort.h"

#include <utility>
#include <cstdlib>

void Sort::Quick::Apply(int *data, int start, int end)
{
    int left = start, right = end, x = data[start + (end - start) / 2];
    while (left <= right)
    {
        while (data[left] < x)
            ++left;

        while (data[right] > x)
            --right;

        if (left <= right)
            std::swap(data[left++], data[right--]);
    }
    if (start < right)
        Apply(data, start, right);

    if (left < end)
        Apply(data, left, end);
}

long long Sort::Quick::CountComparisons(int *data, int start, int end)
{
    long long count = 0;
    int left = start, right = end, x = data[start + (end - start) / 2];
    while (++count && left <= right)
    {
        while (++count && data[left] < x)
            ++left;

        while (++count && data[right] > x)
            --right;

        if (++count && left <= right)
            std::swap(data[left++], data[right--]);
    }
    if (++count && start < right)
        count += CountComparisons(data, start, right);

    if (++count && left < end)
        count += CountComparisons(data, left, end);

    return count;
}