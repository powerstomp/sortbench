#include "ShakerSort.h"

#include <utility>

void Sort::Shaker::Apply(int* a, int n) {
	bool swap = false;
	int head = 0, tail = n - 1, k = 0;
	while (head < tail) {
		swap = false;

		for (int i = head; i < tail; i++) {
			if (a[i] > a[i + 1]) {
				std::swap(a[i + 1], a[i]);
				swap = true;
				k = i;
			}
		}
		tail = k;

		if(!swap)
			break;
		swap = false;

		for (int i = tail; i > head; i--) {
			if (a[i] < a[i - 1]) {
				std::swap(a[i - 1], a[i]);
				swap = true;
				k = i;
			}
		}
		head = k;
	}
}

long long Sort::Shaker::CountComparisons(int* a, int n) {
	long long res = 0;
	bool swap = false;
	int head = 0, tail = n - 1, k = 0;
	while (++res && head < tail) {
		swap = false;

		for (int i = head; ++res && i < tail; i++) {
			if (++res && a[i] > a[i + 1]) {
				std::swap(a[i + 1], a[i]);
				swap = true;
				k = i;
			}
		}
		tail = k;

		if(++res && !swap)
			break;
		swap = false;

		for (int i = tail; ++res && i > head; i--) {
			if (++res && a[i] < a[i - 1]) {
				std::swap(a[i - 1], a[i]);
				swap = true;
				k = i;
			}
		}
		head = k;
	}
	return res;
}