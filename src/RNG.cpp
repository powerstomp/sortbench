#include "RNG.h"
#include <random>
#include <chrono>

namespace ch = std::chrono;

static std::mt19937 rng(ch::high_resolution_clock::now()
								.time_since_epoch().count());

void RNG::FillSorted(int *values, int n) {
	for (int i = 0; i < n; i++)
		values[i] = i;
}
void RNG::FillReverseSorted(int *values, int n) {
	for (int i = 0; i < n; i++)
		values[i] = n - i - 1;
}
void RNG::FillNearlySorted(int *values, int n) {
	FillSorted(values, n);
	for (int i = 0; i < 10; i++)
		std::swap(values[rng() % n], values[rng() % n]);
}
void RNG::FillRandom(int *values, int n) {
	for (int i = 0; i < n; i++)
		values[i] = rng() % n;
}