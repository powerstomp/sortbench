#include "MergeSort.h"

#include <utility>

void Sort::Merge::Apply(int *data, int start, int end)
{
    if (start < end)
    {
        int mid = start + (end - start) / 2;
        Apply(data, start, mid);
        Apply(data, mid + 1, end);

        int i = start, j = mid + 1, k = 0;
        int *temp = new int[end - start + 1];
        while (i <= mid && j <= end)
            if (data[i] < data[j])
                temp[k++] = data[i++];

            else
                temp[k++] = data[j++];

        while (i <= mid)
            temp[k++] = data[i++];

        while (j <= end)
            temp[k++] = data[j++];

        for (int i = start, k = 0; i <= end; i++, k++)
            data[i] = temp[k];

        delete[] temp;
    }
}

int Sort::Merge::CountComparisons(int *data, int start, int end)
{
    int count = 0;
    if (start < end)
    {
        int mid = start + (end - start) / 2;
        count += CountComparisons(data, start, mid);
        count += CountComparisons(data, mid + 1, end);

        int i = start, j = mid + 1, k = 0;
        int *temp = new int[end - start + 1];
        while (++count && i <= mid && j <= end)
            if (++count && data[i] < data[j])
                temp[k++] = data[i++];

            else
                temp[k++] = data[j++];

        while (++count && i <= mid)
            temp[k++] = data[i++];

        while (++count && j <= end)
            temp[k++] = data[j++];

        for (int i = start, k = 0; ++count && i <= end; i++, k++)
            data[i] = temp[k];

        delete[] temp;
    }
    return count;
}