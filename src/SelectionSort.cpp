#include "SelectionSort.h"

#include <utility>

void Sort::Selection::Apply(int *data, int n) {
	for (int i = 0; i < n - 1; ++i) {
		int min = i, minValue = data[i];
		for (int j = i + 1; j < n; ++j) {
			if (data[j] < minValue) {
				min = j;
				minValue = data[j];
			}
		}
		if (min != i)
			std::swap(data[i], data[min]);
	}
}

long long Sort::Selection::CountComparisons(int *data, int n) {
	long long count = 0;
	for (int i = 0; ++count && i < n - 1; i++) {
		int min = i, minValue = data[i];
		for (int j = i + 1; ++count && j < n; j++) {
			if (++count && data[j] < minValue) {
				min = j;
				minValue = data[j];
			}
		}
		if (++count && min != i)
			std::swap(data[i], data[min]);
	}
	return count;
}