#include "Types.h"
#include "BubbleSort.h"

#include <fstream>
#include <iostream>

#define EXIT(id, msg) { std::cout << msg; return (id); }

int* LoadFile(const char *name, int &n) {
	std::ifstream file(name);
	if (!file.good())
		return nullptr;

	file >> n;

	int *values = new int[n];
	for (int i = 0; i < n; i++)
		file >> values[i];

	return values;
}
bool WriteFile(const char *name, int *values, int n) {
	std::ofstream file(name);
	if (!file.good())
		return false;

	file << n << '\n';
	for (int i = 0; i < n; i++)
		file << values[i] << ' ';

	return true;
}

/*
	1: Argument not found
	2: Invalid argument
*/
int main(int argc, char **argv) {
	if (argc < 4)
		EXIT(1, "Not enough arguments.");

	if (strcmp(argv[1], "-a") == 0) {
		int algo = ParseOption(argv[2], SORTS, SORT_COUNT);
		if (algo == -1)
			EXIT(2, "Invalid algorithm.");

		int tmp, outputFlags = 0;
		while ((tmp = ParseOption(argv[argc - 1],
							OUTPUT_TYPES, OUTPUT_TYPE_COUNT)) != -1) {
			outputFlags |= tmp;
			argc--;
		}
		if (outputFlags == 0)
			EXIT(1, "No outputs provided.");

		int n, order = -1;
		int *values = LoadFile(argv[3], n);
		if (!values) {
			n = atoi(argv[3]);

			if (argc > 4) {
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
	} else if (strcmp(argv[1], "-c") == 0) {
		if (argc < 5)
			EXIT(1, "Not enough arguments.");

		int algo = ParseOption(argv[2], SORTS, SORT_COUNT),
			algo2 = ParseOption(argv[3], SORTS, SORT_COUNT);
		if (algo == -1 || algo2 == -1)
			EXIT(2, "Invalid algorithm.");

		int n, order;
		int *values;
		if (argc == 5) {
			if (!(values = LoadFile(argv[4], n)))
				EXIT(2, "File not found.");
		} else {
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
			std::cout << "Input order:\t" << INPUT_ORDER_NAMES[order] << '\n';
	} else
		EXIT(2, "Invalid mode.");

	return 0;
}