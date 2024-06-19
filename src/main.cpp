#include "Types.h"
#include "BubbleSort.h"
#include "InsertionSort.h"
#include "HeapSort.h"
#include "SelectionSort.h"
#include "QuickSort.h"
#include "MergeSort.h"
#include "CountingSort.h"
#include "RNG.h"
#include "Stopwatch.h"

#include <cassert>
#include <fstream>
#include <iostream>

#define EXIT(id, msg)     \
	{                     \
		std::cout << msg; \
		return (id);      \
	}

bool IsSorted(int *values, int n)
{
	for (int i = 0; i < n - 1; i++)
		if (values[i] > values[i + 1])
			return false;
	return true;
}

int *LoadFile(const char *name, int &n)
{
	std::ifstream file(name);
	if (!file.good())
		return nullptr;

	file >> n;

	int *values = new int[n];
	for (int i = 0; i < n; i++)
		file >> values[i];

	return values;
}

bool WriteFile(const char *name, int *values, int n)
{
	std::ofstream file(name);
	if (!file.good())
		return false;

	file << n << '\n';
	for (int i = 0; i < n; i++)
		file << values[i] << ' ';

	return true;
}

long long GetSortTime(int algorithm, int *values, int n)
{
	static Stopwatch stopwatch;

#define BENCH(command)               \
	{                                \
		stopwatch.Start();           \
		{                            \
			command;                 \
		}                            \
		assert(IsSorted(values, n)); \
		return stopwatch.Get();      \
	}

	if (algorithm == SortType::Bubble)
		BENCH(Sort::Bubble::Apply(values, n))
	else if (algorithm == SortType::Insertion)
		BENCH(Sort::Insertion::Apply(values, n))
	else if (algorithm == SortType::Heap)
		BENCH(Sort::Heap::Apply(values, n))
	else if (algorithm == SortType::Selection)
		BENCH(Sort::Selection::Apply(values, n))
	else if (algorithm == SortType::Quick)
		BENCH(Sort::Quick::Apply(values, 0, n - 1))
	else if (algorithm == SortType::Merge)
		BENCH(Sort::Merge::Apply(values, 0, n - 1))
	else if (algorithm == SortType::Counting)
		BENCH(Sort::Counting::Apply(values, n))

#undef BENCH

	return -1;
}

long long GetSortComparisons(int algorithm, int *values, int n)
{
#define BENCH(command)               \
	{                                \
		long long result = command;  \
		assert(IsSorted(values, n)); \
		return result;               \
	}

	if (algorithm == SortType::Bubble)
		BENCH(Sort::Bubble::CountComparisons(values, n))
	else if (algorithm == SortType::Insertion)
		BENCH(Sort::Insertion::CountComparisons(values, n))
	else if (algorithm == SortType::Heap)
		BENCH(Sort::Heap::CountComparisons(values, n))
	else if (algorithm == SortType::Selection)
		BENCH(Sort::Selection::CountComparisons(values, n))
	else if (algorithm == SortType::Quick)
		BENCH(Sort::Quick::CountComparisons(values, 0, n - 1))
	else if (algorithm == SortType::Merge)
		BENCH(Sort::Merge::CountComparisons(values, 0, n - 1))
	else if (algorithm == SortType::Counting)
		BENCH(Sort::Counting::CountComparisons(values, n))

	return -1;
}

void RunBenchmark(int algorithm, int *values, int n, int flags)
{
	int *tmp = new int[n];
	std::memcpy(tmp, values, n * sizeof(tmp[0]));

	std::cout << "--------------------------------\n";
	if (flags & OutputType::Time)
		std::cout << "Running time:\t" << GetSortTime(algorithm, values, n) / 1e6 << "ms" << '\n';
	if (flags & OutputType::Comparisons)
	{
		std::memcpy(values, tmp, n * sizeof(values[0]));
		std::cout << "Comparisons:\t" << GetSortComparisons(algorithm, values, n) << '\n';
	}
	std::cout << '\n';

	delete[] tmp;
}

void RunComparison(int algorithm, int algorithm2,
				   int *values, int n)
{
	int *tmp = new int[n];
	std::memcpy(tmp, values, n * sizeof(tmp[0]));

	std::cout << "--------------------------------\n";
	std::cout << "Running time:\t" << GetSortTime(algorithm, values, n) / 1e6 << "ms";
	std::memcpy(values, tmp, n * sizeof(values[0]));
	std::cout << "\t|\t" << GetSortTime(algorithm2, values, n) / 1e6 << "ms" << '\n';

	std::memcpy(values, tmp, n * sizeof(values[0]));
	std::cout << "Comparisons:\t" << GetSortComparisons(algorithm, values, n);
	std::memcpy(values, tmp, n * sizeof(values[0]));
	std::cout << "\t|\t" << GetSortComparisons(algorithm2, values, n) << '\n';

	std::cout << '\n';

	delete[] tmp;
}

/*
	Commands:
		1: Algorithm, input file
		2: Algorithm, n with order
		3: Algorithm, n
		4: Comparison, input file
		5: Comparison, n
	Exit codes:
		1: Argument not found
		2: Invalid argument
*/
int main(int argc, char **argv)
{
	if (argc < 4)
		EXIT(1, "Not enough arguments.");

	if (strcmp(argv[1], "-a") == 0)
	{
		int algo = ParseOption(argv[2], SORTS, SORT_COUNT);
		if (algo == -1)
			EXIT(2, "Invalid algorithm.");

		int tmp, outputFlags = 0;
		while ((tmp = ParseOption(argv[argc - 1],
								  OUTPUT_TYPES, OUTPUT_TYPE_COUNT)) != -1)
		{
			outputFlags |= tmp;
			argc--;
		}
		if (outputFlags == 0)
			EXIT(1, "No outputs provided.");

		int n, order = -1;
		int *values = LoadFile(argv[3], n);
		if (!values)
		{
			n = atoi(argv[3]);

			if (argc > 4)
			{
				order = ParseOption(argv[4], INPUT_ORDERS, INPUT_ORDER_COUNT);
				if (order == -1)
					EXIT(2, "Invalid input order.");
			}
		}

		std::cout << "ALGORITHM MODE\n";
		std::cout << "Algorithm:\t" << SORT_NAMES[algo] << '\n';
		if (values)
			std::cout << "Input file:\t" << argv[3] << '\n';
		std::cout << "Input size:\t" << n << '\n';

		if (values)
		{
			RunBenchmark(algo, values, n, outputFlags);
			WriteFile("output.txt", values, n);
		}
		else
		{
			values = new int[n];
			if (order == -1 || order == InputOrder::Random)
			{
				std::cout << "\nInput order: Random\n";
				RNG::FillRandom(values, n);
				WriteFile(order == -1 ? "input_1.txt" : "input.txt",
						  values, n);
				RunBenchmark(algo, values, n, outputFlags);
			}
			if (order == -1 || order == InputOrder::NearlySorted)
			{
				std::cout << "\nInput order: Nearly Sorted\n";
				RNG::FillNearlySorted(values, n);
				WriteFile(order == -1 ? "input_2.txt" : "input.txt",
						  values, n);
				RunBenchmark(algo, values, n, outputFlags);
			}
			if (order == -1 || order == InputOrder::Sorted)
			{
				std::cout << "\nInput order: Sorted\n";
				RNG::FillSorted(values, n);
				WriteFile(order == -1 ? "input_3.txt" : "input.txt",
						  values, n);
				RunBenchmark(algo, values, n, outputFlags);
			}
			if (order == -1 || order == InputOrder::ReverseSorted)
			{
				std::cout << "\nInput order: Reverse Sorted\n";
				RNG::FillReverseSorted(values, n);
				WriteFile(order == -1 ? "input_4.txt" : "input.txt",
						  values, n);
				RunBenchmark(algo, values, n, outputFlags);
			}
			if (order != -1)
				WriteFile("output.txt", values, n);
		}

		delete[] values;
	}
	else if (strcmp(argv[1], "-c") == 0)
	{
		if (argc < 5)
			EXIT(1, "Not enough arguments.");

		int algo = ParseOption(argv[2], SORTS, SORT_COUNT),
			algo2 = ParseOption(argv[3], SORTS, SORT_COUNT);
		if (algo == -1 || algo2 == -1)
			EXIT(2, "Invalid algorithm.");

		int n, order;
		int *values = nullptr;
		if (argc == 5)
		{
			if (!(values = LoadFile(argv[4], n)))
				EXIT(2, "File not found.");
		}
		else
		{
			n = atoi(argv[4]);
			order = ParseOption(argv[5], INPUT_ORDERS, INPUT_ORDER_COUNT);
			if (order == -1)
				EXIT(2, "Invalid input order.");
		}

		std::cout << "COMPARE MODE\n";
		std::cout << "Algorithm:\t" << SORT_NAMES[algo] << "\t|\t" << SORT_NAMES[algo2] << '\n';
		if (values)
			std::cout << "Input file:\t" << argv[4] << '\n';
		std::cout << "Input size:\t" << n << '\n';

		if (!values)
		{
			values = new int[n];

			std::cout << "\nInput order: " << INPUT_ORDER_NAMES[order] << '\n';
			if (order == InputOrder::Random)
				RNG::FillRandom(values, n);
			if (order == InputOrder::NearlySorted)
				RNG::FillNearlySorted(values, n);
			if (order == InputOrder::Sorted)
				RNG::FillSorted(values, n);
			else if (order == InputOrder::ReverseSorted)
				RNG::FillReverseSorted(values, n);

			WriteFile("input.txt", values, n);
		}
		RunComparison(algo, algo2, values, n);

		delete[] values;
	}
	else
		EXIT(2, "Invalid mode.");

	return 0;
}