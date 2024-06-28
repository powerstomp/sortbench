#include "ShellSort.h"

#include <utility>

void Sort::Shell::Apply(int *data, int n)
{
    for (int gap = n/2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i++)
        {
        
            for (int j = i;
			     j >= gap && data[j - gap] > data[j];
			     j -= gap)
                 	std::swap(data[j], data[j - gap]);
        }
    }
    return;
}

long long Sort::Shell::CountComparisons(int *data, int n)
{
    long long count = 0;
    for (int gap = n/2; ++count && gap > 0; gap /= 2)
    {
        for (int i = gap; ++count && i < n; i++)
        {
        
            for (int j = i;
			     ++++count && j >= gap && data[j - gap] > data[j];
			     j -= gap)
                 	std::swap(data[j], data[j - gap]);
        }
    }
    return count;
}