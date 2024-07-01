#include "BubbleSort.h"

#include <utility>

void Sort::Bubble::Apply(int *data, int n) {
	for (int step = 0; step < n - 1; step++) {
		bool swapped = false;
		for (int i = 0; i < n - step - 1; i++) {
			if (data[i] > data[i + 1]) {
				std::swap(data[i], data[i + 1]);
				swapped = true;
			}
		}
		if (!swapped)
			break;
	}
}
long long Sort::Bubble::CountComparisons(int *data, int n) {
	long long count = 0;
	for (int step = 0; ++count && step < n - 1; step++) {
		bool swapped = false;
		for (int i = 0; ++count && i < n - step - 1; i++) {
			if (++count && data[i] > data[i + 1]) {
				std::swap(data[i], data[i + 1]);
				swapped = true;
			}
		}
		if (++count && !swapped)
			break;
	}
	return count;
}