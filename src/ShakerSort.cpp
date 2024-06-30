#include "ShakerSort.h"

void Sort::Shaker::Apply(int* a, int n)
{
    int head = 0, tail = n - 1, k = 0;
    while (head < tail)
    {
        for (int i = head; i < tail; i++)
        {
            if (a[i] > a[i + 1])
            {
                std::swap(a[i+1], a[i]);
                k = i;
            }
        }
        tail = k;
        for (int i = tail; i > head; i--)
        {
            if (a[i] < a[i - 1])
            {
                //int temp = a[i - 1];
                //a[i - 1] = a[i];
                //a[i] = temp;
                std::swap(a[i-1], a[i]);
                k = i;
            }
        }
        head = k;
    }
}

long long Sort::Shaker::CountComparisons(int* a, int n)
{
    long long res = 0;
    int head = 0, tail = n - 1, k = 0;
    while (++res && head < tail)
    {
        for (int i = head; ++res && i < tail; i++)
        {
            if (++res && a[i] > a[i + 1])
            {
                std::swap(a[i+1], a[i]);
                k = i;
            }
        }
        tail = k;
        for (int i = tail; ++res && i > head; i--)
        {
            if (++res && a[i] < a[i - 1])
            {
                //int temp = a[i - 1];
                //a[i - 1] = a[i];
                //a[i] = temp;
                std::swap(a[i-1], a[i]);
                k = i;
            }
        }
        head = k;
    }
    return res;
}