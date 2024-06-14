#include "BubbleSort.h"

#include <utility>

void Sort::Bubble::Apply(int *data, int n) {
	for (int i = 0; i < n - 1; i++)
		for (int j = i + 1; j < n; j++)
			if (data[i] > data[j])
				std::swap(data[i], data[j]);
}
int Sort::Bubble::CountComparisons(int *data, int n) {
	int count = 0;
	for (int i = 0; ++count && i < n - 1; i++)
		for (int j = i + 1; ++count && j < n; j++)
			if (++count && data[i] > data[j])
				;
	return count;
}