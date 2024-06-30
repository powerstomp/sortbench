#include "RNG.h"
#include <random>
#include <chrono>

namespace ch = std::chrono;

#ifndef FORCE_SEED
static const auto SEED = ch::high_resolution_clock::now()
								.time_since_epoch().count();
#else
static const auto SEED = 24341337;
#endif

static std::mt19937 rng(SEED);

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