#include "FlashSort.h"

#include <cmath>
#include <utility>

#define GetBucket(x) ((bucketCount - 1ll) * ((x) - minVal) / (maxVal - minVal))

void Sort::Flash::Apply(int* data, int n) {
	if (n <= 1)
		return;

	int bucketCount = floor(n * 0.45);
	if (bucketCount < 2)
		bucketCount = 2;
	int elementCounts[bucketCount] = {0};

	int minVal = data[0], maxVal = data[0];
	for (int i = 1; i < n; i++) {
		if (data[i] < minVal)
			minVal = data[i];
		if (data[i] > maxVal)
			maxVal = data[i];
	}
	if (minVal == maxVal)
		return;

	for (int i = 0; i < n; i++)
		elementCounts[GetBucket(data[i])]++;
	for (int i = 1; i < bucketCount; i++)
		elementCounts[i] += elementCounts[i - 1];

	int count = 0, index = 0;
	while (count < n) {
		int curBucket = GetBucket(data[index]);
		while (index >= elementCounts[curBucket]) {
			index++;
			curBucket = GetBucket(data[index]);
		}
		int temp = data[index];
		while (index < elementCounts[curBucket]) {
			curBucket = GetBucket(temp);
			elementCounts[curBucket]--;
			std::swap(temp, data[elementCounts[curBucket]]);
			count++;
		}
	}

	for (int i = 1; i < n; i++) {
		int key = data[i], j = i - 1;
		while (j >= 0 && data[j] > key) {
			data[j + 1] = data[j];
			j--;
		}
		data[j + 1] = key;
	}

	return;
}

long long Sort::Flash::CountComparisons(int* data, int n) {
	long long res = 0;

	if (++res && n <= 1)
		return res;

	int bucketCount = floor(n * 0.45);
	if (++res && bucketCount < 2)
		bucketCount = 2;
	int elementCounts[bucketCount] = {0};

	int minVal = data[0], maxVal = data[0];
	for (int i = 1; ++res && i < n; i++) {
		if (++res && data[i] < minVal)
			minVal = data[i];
		if (++res && data[i] > maxVal)
			maxVal = data[i];
	}
	if (++res && minVal == maxVal)
		return res;

	for (int i = 0; ++res && i < n; i++)
		elementCounts[GetBucket(data[i])]++;
	for (int i = 1; ++res && i < bucketCount; i++)
		elementCounts[i] += elementCounts[i - 1];

	int count = 0, index = 0;
	while (++res && count < n) {
		int curBucket = GetBucket(data[index]);
		while (++res && index >= elementCounts[curBucket]) {
			index++;
			curBucket = GetBucket(data[index]);
		}
		int temp = data[index];
		while (++res && index < elementCounts[curBucket]) {
			curBucket = GetBucket(temp);
			elementCounts[curBucket]--;
			std::swap(temp, data[elementCounts[curBucket]]);
			count++;
		}
	}

	for (int i = 1; ++res && i < n; i++) {
		int key = data[i], j = i - 1;
		while (++res && j >= 0 && ++res && data[j] > key) {
			data[j + 1] = data[j];
			j--;
		}
		data[j + 1] = key;
	}

	return res;
}
